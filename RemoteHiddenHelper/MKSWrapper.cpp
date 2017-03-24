#include "MKSWrapper.h"

#include <qfile.h>
#include <qprocess.h>
#include <QDatastream>
#include <qapplication.h>
#include <qcursor.h>
#include <QMouseEvent>
#include <qthread.h>
#include <windows.h>
#include <tchar.h>


#include "Util.h"

#define MKSCLIENT "si.exe"



static void LeftClick(int x, int y)
{
    mouse_event((int)MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event((int)MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

static void PressShift(int key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = VK_SHIFT;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Press the "V" key
    ip.ki.wVk = key;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "V" key
    ip.ki.wVk = key;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "Ctrl" key
    ip.ki.wVk = VK_SHIFT;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
    QThread::msleep(10);
}

static void Press(int key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "A" key
    ip.ki.wVk = key; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
    QThread::msleep(10);
}

namespace RW{
	namespace CORE{

		MKSWrapper::MKSWrapper(QObject* Parent) : BasicWrapper(Parent),
			m_MKSLocation("")
		{
            m_Destination = "C:\\Temp\\";
		}


		MKSWrapper::~MKSWrapper()
		{
		}

		void MKSWrapper::OnProcessMessage(COM::Message Msg)
		{
			switch (Msg.MessageID())
			{
			case COM::MessageDescription::EX_MKSLogin:
            {
                QString location = "";
                QString username = "";
                QString password = "";
				location = Msg.ParameterList()[0].toString();
				username = Msg.ParameterList()[1].toString();
				password = Msg.ParameterList()[2].toString();

                StartMKS(location, username, password);
                break;
            }
			case COM::MessageDescription::EX_MKSCreateSandBox:
			{
				QString MKSUrl = "";
				QString Destination = "";
				MKSUrl = Msg.ParameterList()[0].toString();
				Destination = Msg.ParameterList()[1].toString();

                CreateSandBox(MKSUrl, Destination);
				break;
			}
			case COM::MessageDescription::EX_MKSDropSandbox:
				DropSandBox();
				break;
			case COM::MessageDescription::EX_MKSClose:
				CloseMKS();
				break;
			default:
				break;
			}
		}



		/***************************************************************************************************************//**
		@autor Ivo Kunadt
		@brief 
		@param MKSLocation
		@param Username
		@param Password
		@param Server 
		@param Port Port des MKS Servers
		@param Proxy Proxy Adresse des MKS Servers
		@param ProxyPort Proxy Port des MKS Servers
		@return void
		********************************************************************************************************************/
		void MKSWrapper::StartMKS(QString MKSLocation,QString Username, QString Password, QString Server, quint16 Port, QString Proxy, quint16 ProxyPort)
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_MKSLogin);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);


			if (Username.isEmpty() ||
				Password.isEmpty() ||
				Server.isEmpty() ||
				Port == 0 ||
				Proxy.isEmpty() ||
				ProxyPort == 0)
			{
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSMissingParameter));
                emit NewMessage(msg);
			}

			m_MKSLocation = MKSLocation;
			m_Port = Port;
			m_ProxyPort = ProxyPort;
			m_ProxyServer = Server;
			m_Server = Server;

			QProcess proc;
			if (!QFile(m_MKSLocation).exists())
			{
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSLocationMissing));
                emit NewMessage(msg);
                return;
			}

            //Sofern MKS noch offen ist muss es hier geschlossen werden
            if (GetProcessByName("IntegrityClient.exe"))
            {
                CloseMKS();
            }

			QStringList arguments;
            arguments << "diag" << "--diag=""setproxy""" << "--param=" + Server + ":" + QString::number(Port) + "" << "--param=" + Proxy + ":" + QString::number(ProxyPort) + "" << "--target=""client""";
			proc.start(MKSLocation + MKSCLIENT, arguments);
			if (!proc.waitForFinished(5000))
			{
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSError));
                emit NewMessage(msg);
                return;
			}

			arguments.clear();
            arguments << "connect" << "--gui" << "--hostname=""ims-id""" << "--port=" + QString::number(Port) + "" << "--user=" + Username + "" << "--password=" + Password + "";

            QProcess procLogin;
            procLogin.start(MKSLocation + MKSCLIENT, arguments);

            PrepareMKSLoginForm();

            if (!procLogin.waitForFinished(60000))
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSLogin));
                emit NewMessage(msg);
            }

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}


		/***************************************************************************************************************//**
		@autor Ivo Kunadt
		@brief Erzeugt eine Sandbox für den übergebeben MKS Link. Dabei wird zunächst etwaige ältere Sandboxen mit dem gleichen Link
		gelöscht. Sobald die Daten durch erzeugen der Sandbox herunter geladen sind, wird die erzeugte Sandbox wieder zerstört.
		@param MksUrl MKSLink für den der MKS Client die SandBox erzeugen soll.
		@param Destination Ziel der Ablage, der Downloadfiles
		@return void
		********************************************************************************************************************/
		void MKSWrapper::CreateSandBox(QString MksUrl, QString Destination)
		{
			QProcess proc;
			QStringList arguments;

            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_MKSCreateSandBox);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            //! \todobrauchen wir das noch hier
            //QString dest = GetMKSLink(m_Destination, MksUrl);
            QString dest = Destination;
            
            if (QFile(m_Destination + dest).exists())
            {
                msg.SetSuccess(true);
                emit NewMessage(msg);
                return;
            }

            arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << dest + "/project.pj";
            proc.start(m_MKSLocation + MKSCLIENT, arguments);
            proc.waitForFinished(10000);

            arguments.clear();
            arguments << "createsandbox" << "--yes" << "--status=""default""" << "--hostname=" + m_Server + "" << "--port=" + QString::number(m_Port) + "" << "--project=" + MksUrl << m_Destination + dest;
            
            QProcess procStart;
            procStart.start(m_MKSLocation + MKSCLIENT, arguments);

            if (!procStart.waitForFinished(180000))
			{
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSSandBoxCreation));
                emit NewMessage(msg);
			}
			else
			{
                QProcess procCleanUp;
                arguments.clear();
                arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << dest + "/project.pj";
                procCleanUp.start(m_MKSLocation + MKSCLIENT, arguments);
                procCleanUp.waitForFinished(10000);

                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
                msg.SetSuccess(true);
                emit NewMessage(msg);
			}
		}

		void MKSWrapper::DropSandBox()
		{
			QProcess proc;
			QStringList arguments;

            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_MKSDropSandbox);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);


			arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << "--port=" + QString(m_Port) + "" << m_Destination + "project.pj";
			
			proc.start(m_MKSLocation + MKSCLIENT, arguments);
			if (proc.waitForFinished(10000))
			{
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSSanbBoxDrop));
                msg.SetSuccess(true);
                emit NewMessage(msg);
                return;
			}

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}

		void MKSWrapper::CloseMKS()
		{
			QProcess proc;
			QStringList arguments;


            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_MKSCreateSandBox);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			arguments << "exit";

			proc.start(m_MKSLocation + MKSCLIENT, arguments);
			if (!proc.waitForFinished(30000))
			{
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorMKSCloseFailed));
                msg.SetSuccess(true);
                emit NewMessage(msg);
                return;
			}
            //Warten bis MKS wirklich weg ist
            QThread::msleep(1000);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}

		void MKSWrapper::PrepareMKSLoginForm()
		{
			do{
				HWND handle = GetForegroundWindow();
				char wnd_title[256];
				HWND hwnd = GetForegroundWindow(); // get handle of currently active window
				GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
				if (strcmp(wnd_title, "Error") == 0)
					break;
				QThread::msleep(100);
			} while (true);

			QCursor* c = QApplication::overrideCursor();

			//Error Dialog bestätigen
			c->setPos(1024, 574);
			QThread::msleep(10);
			LeftClick(1024, 574);
			QThread::msleep(200);

			//Vorausgefüllter Loginform bestätigen
			c->setPos(880, 600);
			QThread::msleep(10);
			LeftClick(880, 600);
			QThread::msleep(200);

			//Zum Usernamenfeld navigieren
			c->setPos(922, 546);
			QThread::msleep(10);
			LeftClick(922, 546);
			QThread::msleep(200);

			//Username
			Press(0x45);
			Press(0x58);
			Press(0x54);
			Press(0x54);
			Press(0x32);
			Press(0x36);
			Press(0x39);
			Press(0x39);

			//Zum Password navigieren
			Press(VK_TAB);

			//Password
			Press(0x33);
			PressShift(0x34);
			Press(0x53);
			PressShift(0x47);
			Press(0x5A);
			Press(0x36);
			Press(0x53);
			PressShift(0x53);

			//Loginform bestätigen
			c->setPos(880, 600);
			LeftClick(880, 600);
			QThread::msleep(100);

		}

     
	}
}