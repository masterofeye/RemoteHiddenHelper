#include "FHostSpWrapper.h"
#include <qfileinfo.h>
#include <qdir.h>
#include <qdatastream.h>
#include <qthread.h>
#include "Util.h"


#define PRG_POSTFIX "prg"
#define CFX_POSTFIX "cfx"

BOOL CALLBACK enumWindowsProc(
	__in  HWND hWnd,
	__in  LPARAM lParam
	) {

	int length = ::GetWindowTextLengthA(hWnd);
	if (0 == length) return TRUE;

	char* buffer = new char[length];

	GetWindowTextA(hWnd, buffer, length);
	QString s = QString(buffer);
	if (s.contains("FHostSP"))
	{
		HWND* lumpi = reinterpret_cast<HWND*>(lParam);
		*lumpi = hWnd;
		false;
	}

	delete buffer;
	return TRUE;
}


namespace RW{
	namespace CORE{

		FHostSpWrapper::FHostSpWrapper(QObject* Parent) : BasicWrapper(Parent)
		{
		}


		FHostSpWrapper::~FHostSpWrapper()
		{
		}

		void FHostSpWrapper::OnProcessMessage(COM::Message Msg)
		{
			switch (Msg.MessageID())
			{
			case COM::MessageDescription::EX_FHostSPStartFHost:
				StartFHostSP();
				break;
			case COM::MessageDescription::EX_FHostSPLoadFlashFile:
                LoadSequence(QFile(Msg.ParameterList()[0].toString()));
				break;
			case COM::MessageDescription::EX_FHostSPCloseFHost:
				CloseApplication();
				break;
			case COM::MessageDescription::EX_FHostSPStartFlash:
				StartSequence();
				break;
			case COM::MessageDescription::EX_FHostSPCloseSequence:
                CloseSequence();
                break;
			case COM::MessageDescription::EX_FHostSPGetProgress:
                GetProgress();
                break;
			case COM::MessageDescription::EX_FHostSPGetState:
                GetState();
                break;
			case COM::MessageDescription::EX_FHostSPAbortSequence:
                AbortSequence();
                break;
			case COM::MessageDescription::Amount:
				break;
			default:
				break;
			}

			
		}

		void FHostSpWrapper::StartFHostSP()
		{
			CoInitialize(NULL);

			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_FHostSPStartFHost);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			HRESULT hr = CoCreateInstance(__uuidof(FHostSP_RemoteInterface), NULL, CLSCTX_LOCAL_SERVER/*CLSCTX_ALL*/, __uuidof(IFHostSP_RemoteInterface), (void**)&m_Process);
            if (FAILED(hr))
            {
				msg.SetSuccess(false);

                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPCoCreateInstance));
				emit NewMessage(msg);
                return;
            }
            Sleep(100);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void FHostSpWrapper::CloseSequence()
		{
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_FHostSPCloseSequence);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			HRESULT  hr = m_Process->CloseSequence(_bstr_t(m_WorkspacePath.c_str()));
			if (FAILED(hr))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPSequenceClose));
				emit NewMessage(msg);
                return;
            }
			Sleep(500);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void FHostSpWrapper::GetProgress(){
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_FHostSPGetProgress);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			long stepvalue = 0;
			long sequencevalue = 0;
			long totalvalue = 0;
			HRESULT  hr = m_Process->GetProgress(_bstr_t(m_WorkspacePath.c_str()), &stepvalue, &sequencevalue, &totalvalue);
			if (FAILED(hr))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPGetProgress));
				emit NewMessage(msg);
                return;
            }
            Sleep(100);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void FHostSpWrapper::CloseApplication()
		{
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_FHostSPCloseFHost);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            HRESULT  hr = m_Process->CloseApplication();
			if (FAILED(hr))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPCloseApplication));
				emit NewMessage(msg);
                return;
            }
            m_Process.Detach();
            m_Process.Release();

            CoUninitialize();

            if (GetProcessByName("FHostSp.exe", true))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPStillAlive));
				emit NewMessage(msg);
            }

            Sleep(100);
            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void FHostSpWrapper::GetState()
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FHostSPGetState);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            long sequencestate;
			HRESULT  hr = m_Process->GetState(_bstr_t(m_WorkspacePath.c_str()), &sequencestate);
            if (FAILED(hr))
            {
                msg.SetSuccess(false);
                msg.SetResult("Can't request the current FHostSP state.");
                emit NewMessage(msg);
                return;
            }
            Sleep(500);
            
            m_LifeTimerCounter++;
            if (m_LifeTimerCounter = 20)
            {
                long stepvalue = 0;
                long sequencevalue = 0;
                long totalvalue = 0;
                HRESULT  hr = m_Process->GetProgress(_bstr_t(m_WorkspacePath.c_str()), &stepvalue, &sequencevalue, &totalvalue);
                if (FAILED(hr))
                {
                    msg.SetSuccess(false);
                    msg.SetResult("Can't request the current FHostSP progress.");
                    emit NewMessage(msg);
                    return;
                }
				if (stepvalue == 0 && sequencevalue == 0 && totalvalue == 0)
				{
				}
            }

			QString status = ReadStatusText();

            quint64 qu64sequencestate = sequencestate;

            msg.ParameterList().append(qu64sequencestate);
            msg.ParameterList().append(status);
            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}

		void FHostSpWrapper::AbortSequence()
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FHostSPAbortSequence);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			HRESULT  hr = m_Process->AbortSequence(_bstr_t(m_WorkspacePath.c_str()));
            if (FAILED(hr))
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPAbortFailed));
                emit NewMessage(msg);
                return;
            }
            Sleep(500);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}


		void FHostSpWrapper::LoadSequence(const QFile &Flashfile)
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FHostSPLoadFlashFile);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            if (!Flashfile.exists())
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPFlashfileNotExits));
                emit NewMessage(msg);
                return;
            }

            QFileInfo f = QFileInfo(Flashfile);
			QString filename = f.absoluteFilePath().replace(PRG_POSTFIX, CFX_POSTFIX);
            m_WorkspacePath = f.absoluteFilePath().toStdString();
            if (!QFile(filename).exists())
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPFlashfileNotExits));
                emit NewMessage(msg);
                return;
            }

            HRESULT  hr = m_Process->LoadSequence(_bstr_t(f.absoluteFilePath().toStdString().c_str()), _bstr_t(filename.toStdString().c_str()), _bstr_t("Test"));
            if (FAILED(hr))
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPLoadFlashfileFailed));
                emit NewMessage(msg);
                return;
            }
			long status;
			do
			{
				m_Process->GetState(_bstr_t(m_WorkspacePath.c_str()), &status);
				Sleep(100);
			} while (status == 2);

			do
			{
				m_Process->GetState(_bstr_t(m_WorkspacePath.c_str()), &status);
				Sleep(100);
			} while (status == 3); //3 = JOB_LOADING

			if (status == 5)
			{
				Sleep(100);
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPStateFailed));
                emit NewMessage(msg);
                return;
			}
            Sleep(100);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}

        QString FHostSpWrapper::ReadStatusText()
        {
            const int statusEditId = 1012;
            HWND hwnd[1];
            EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(hwnd));

            //Durch die Kinderelemente suchen
            HWND handleMDIClient = FindWindowExA(hwnd[0], nullptr, "MDIClient", NULL);
            DWORD error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";

            HWND handleAFX = GetWindow(handleMDIClient, GW_CHILD);
            error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";

            HWND last = GetWindow(handleAFX, GW_CHILD);
            error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";
            //Nun sollte es m�glich das Edit Control abzufragen
            HWND edit = GetDlgItem(last, statusEditId);
            error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";

            //Textl�nge des Inhaltes abfragen
            int textLen = (int)SendMessageA(edit, WM_GETTEXTLENGTH, 0, 0) + 1;
            error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";

            if (textLen == 0)
            {
                return "";
            }

            QByteArray arr;
            arr.resize(textLen);
            SendMessageA(edit, WM_GETTEXT, textLen, (LPARAM)arr.data());
            error = GetLastError();
            if (error != ERROR_SUCCESS)
                return "";

            return QString(arr);
        }

		void FHostSpWrapper::StartSequence()
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FHostSPStartFlash);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
            //Safty Sleep
            QThread::msleep(5000);
			//! \todo  Hier sollte der Pfad aus der Konfiguration gelesen werden
			HRESULT  hr = m_Process->StartSequence(_bstr_t(m_WorkspacePath.c_str()), _bstr_t("C:\\Program Files (x86)\\FHostSP\\FHostSP.cfx"));
            if (FAILED(hr))
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFHostSPSequenceStart));;
                emit NewMessage(msg);
                return;
            }
            Sleep(100);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            msg.SetSuccess(true);
            emit NewMessage(msg);
		}

	}
}