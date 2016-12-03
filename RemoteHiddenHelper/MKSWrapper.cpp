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

		void MKSWrapper::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
		{
			if (Util::MessageReceiver::MKSWrapper == Type)
			{
				switch (Func)
				{
                case RW::CORE::Util::Functions::MKSLogin:
                {
                    QString location = "";
                    QString username = "";
                    QString password = "";
                    QDataStream data(Report);
                    data >> location;
                    data >> username;
                    data >> password;

                    StartMKS(location, username, password);
                    break;
                }
				case RW::CORE::Util::Functions::MKSCreateSandBox:
                    CreateSandBox(Report, "C:\\Temp\\test2\\");
					break;
				case RW::CORE::Util::Functions::MKSDropSandbox:
					DropSandBox();
					break;
				default:
					break;
				}

			}
		}



		/*******************************************************************//**
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
			if (Username.isEmpty() ||
				Password.isEmpty() ||
				Server.isEmpty() ||
				Port == 0 ||
				Proxy.isEmpty() ||
				ProxyPort == 0)
			{
				emit NewMessage(Util::Functions::MKSLogin, Util::ErrorID::ErrorMKSMissingParameter, nullptr);
			}

			m_MKSLocation = MKSLocation;
			m_Port = Port;
			m_ProxyPort = ProxyPort;
			m_ProxyServer = Server;
			m_Server = Server;

			QProcess proc;
			if (!QFile(m_MKSLocation).exists())
			{
				emit NewMessage(Util::Functions::MKSLogin, Util::ErrorID::ErrorMKSLocationMissing, nullptr);
                return;
			}

			QStringList arguments;
            arguments << "diag" << "--diag=""setproxy""" << "--param=" + Server + ":" + QString::number(Port) + "" << "--param=" + Proxy + ":" + QString::number(ProxyPort) + "" << "--target=""client""";
            //arguments << "diag" << "--diag=""setproxy""" << "--param=""ims-id:7001""" << "--param=""MKS-PROXY:7023""" << "--target=""client""";
			proc.start(MKSLocation + MKSCLIENT, arguments);
			if (!proc.waitForFinished(2000))
			{
				emit NewMessage(Util::Functions::MKSLogin, Util::ErrorID::ErrorMKSError, nullptr);
                return;
			}

			arguments.clear();
            arguments << "connect" << "--gui" << "--hostname=""ims-id""" << "--port=" + QString::number(Port) + "" << "--user=" + Username + "" << "--password=" + Password + "";
            //arguments << "connect" << "--gui" << "--hostname=""ims-id""" << "--port=""7001""" << "--user=""uidw5301""" << "--password=""Windows2001""";

            QProcess procLogin;
            procLogin.start(MKSLocation + MKSCLIENT, arguments);

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

            c->setPos(1024, 574);
            QThread::msleep(10);
            LeftClick(1024, 574);
            QThread::msleep(500);

            c->setPos(880, 600);
            QThread::msleep(10);
            LeftClick(880, 600);
            QThread::msleep(500);
            c->setPos(922, 546);
            QThread::msleep(10);
            LeftClick(922, 546);
            QThread::msleep(500);

            
            Press(0x45);
            Press(0x58);
            Press(0x54);
            Press(0x54);
            Press(0x32);
            Press(0x36);
            Press(0x39);
            Press(0x39);

            Press(VK_TAB);
            
            Press(0x33);
            PressShift(0x34);
            Press(0x53);
            PressShift(0x47);
            Press(0x5A);
            Press(0x36);
            Press(0x53);
            PressShift(0x53);

            c->setPos(880, 600);
            LeftClick(880, 600);
            QThread::msleep(100);

            procLogin.waitForFinished(60000);


			
			emit NewMessage(Util::Functions::MKSLogin, Util::ErrorID::Success, nullptr);
		}

		void MKSWrapper::CreateSandBox(QString MksUrl, QString Destination)
		{
			QProcess proc;
			QStringList arguments;

            QString dest = GetMKSLink(m_Destination, MksUrl);
            
            arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << dest + "/project.pj";
            proc.start(m_MKSLocation + MKSCLIENT, arguments);
            proc.waitForFinished(10000);

            arguments.clear();
            arguments << "createsandbox" << "--yes" << "--status=""default""" << "--hostname=" + m_Server + "" << "--port=" + QString::number(m_Port) + "" << "--project=" + MksUrl << dest;
            
            QProcess procStart;
            procStart.start(m_MKSLocation + MKSCLIENT, arguments);

            

            if (!procStart.waitForFinished(180000))
			{
				emit NewMessage(Util::Functions::MKSCreateSandBox, Util::ErrorID::ErrorMKSSandBoxCreation, nullptr);
			}
			else
			{
                QProcess procCleanUp;
                arguments.clear();
                arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << dest + "/project.pj";
                procCleanUp.start(m_MKSLocation + MKSCLIENT, arguments);
                procCleanUp.waitForFinished(10000);
				emit NewMessage(Util::Functions::MKSCreateSandBox, Util::ErrorID::Success, nullptr);
			}
		}

		//void MKSWrapper::DownloadFlashFiles(QString MksUrl, QString Destination)
		//{
		//	QProcess proc;
		//	QStringList arguments;

		//	arguments << "createsandbox" << "--yes" << "--status=""default""" << "--hostname=" + m_Server + "" << "--port=" + QString(m_Port) + "" << "--project=" + MksUrl + "";

		//	proc.start(m_MKSLocation + MKSCLIENT, arguments);

		//	emit NewMessage((quint16)States::Success, nullptr);
		//}

		void MKSWrapper::DropSandBox()
		{
			QProcess proc;
			QStringList arguments;

			arguments << "dropsandbox" << "--yes" << "--delete=""none""" << "--status=""none""" << "--port=" + QString(m_Port) + "" << m_Destination + "project.pj";
			
			proc.start(m_MKSLocation + MKSCLIENT, arguments);
			if (proc.waitForFinished(10000))
			{
				emit NewMessage(Util::Functions::MKSDropSandbox, Util::ErrorID::ErrorMKSSanbBoxDrop, nullptr);
			}

			emit NewMessage(Util::Functions::MKSDropSandbox, Util::ErrorID::Success, nullptr);
		}


	}
}