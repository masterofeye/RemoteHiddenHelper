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

		void FHostSpWrapper::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
		{
			if (Util::MessageReceiver::FHostSPWrapper == Type)
			{
				switch (Func)
				{
				case RW::CORE::Util::Functions::FHostSPStartFHost:
					StartFHostSP();
					break;
				case RW::CORE::Util::Functions::FHostSPLoadFlashFile:
                    LoadSequence(QFile(Report));
					break;
				case RW::CORE::Util::Functions::FHostSPCloseFHost:
					CloseApplication();
					break;
				case RW::CORE::Util::Functions::FHostSPStartFlash:
					StartSequence();
					break;
                case RW::CORE::Util::Functions::FHostSPCloseSequence:
                    CloseSequence();
                    break;
                case RW::CORE::Util::Functions::FHostSPGetProgress:
                    GetProgress();
                    break;
                case RW::CORE::Util::Functions::FHostSPGetState:
                    GetState();
                    break;
                case RW::CORE::Util::Functions::FHostSPAbortSequence:
                    AbortSequence();
                    break;
				case RW::CORE::Util::Functions::Amount:
					break;
				default:
					break;
				}

			}
		}

		void FHostSpWrapper::StartFHostSP()
		{
			CoInitialize(NULL);

            //! \todo MagicNumber und implementierung
            //if (GetProcessByName("FHostSp.exe"))
            //{

            //}


			HRESULT hr = CoCreateInstance(__uuidof(FHostSP_RemoteInterface), NULL, CLSCTX_LOCAL_SERVER/*CLSCTX_ALL*/, __uuidof(IFHostSP_RemoteInterface), (void**)&m_Process);
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPStartFHost, Util::ErrorID::ErrorFHostSPStartApplication, "");
                return;
            }
            Sleep(100);

			emit NewMessage(Util::Functions::FHostSPStartFHost, Util::ErrorID::Success, "");
		}

		void FHostSpWrapper::CloseSequence()
		{
			HRESULT  hr = m_Process->CloseSequence(_bstr_t(m_WorkspacePath.c_str()));
			if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPStartFHost, Util::ErrorID::ErrorFHostSPSequenceStop, "");
                return;
            }
			Sleep(500);
			emit NewMessage(Util::Functions::FHostSPCloseFHost, Util::ErrorID::Success, "");
		}
		void FHostSpWrapper::GetProgress(){

			long stepvalue = 0;
			long sequencevalue = 0;
			long totalvalue = 0;
			HRESULT  hr = m_Process->GetProgress(_bstr_t(m_WorkspacePath.c_str()), &stepvalue, &sequencevalue, &totalvalue);
			if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPGetProgress, Util::ErrorID::ErrorFHostSPGetProgress, "");
                return;
            }
            Sleep(100);
			emit NewMessage(Util::Functions::FHostSPGetProgress, Util::ErrorID::Success, "");
		}
		void FHostSpWrapper::CloseApplication()
		{
            HRESULT  hr = m_Process->CloseApplication();
			if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPCloseFHost, Util::ErrorID::ErrorFHostSPCloseApplication, "");
                return;
            }
            m_Process.Detach();
            m_Process.Release();

            CoUninitialize();

            if (GetProcessByName("FHostSp.exe", true))
            {
                emit NewMessage(Util::Functions::FHostSPCloseFHost, Util::ErrorID::ErrorFHostSPCloseApplication, "");
            }

            Sleep(100);
			emit NewMessage(Util::Functions::FHostSPCloseFHost, Util::ErrorID::Success, "");
		}
		void FHostSpWrapper::GetState()
		{
            long sequencestate;
			HRESULT  hr = m_Process->GetState(_bstr_t(m_WorkspacePath.c_str()), &sequencestate);
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPGetState, Util::ErrorID::ErrorFHostSPGetStateFailed, "");
                return;
            }
            Sleep(500);

			QString status = ReadStatusText();

            quint64 qu64sequencestate = sequencestate;
            QByteArray arr;
            QDataStream data(&arr,QIODevice::WriteOnly);
            data << qu64sequencestate;
			data << status;

			emit NewMessage(Util::Functions::FHostSPGetState, Util::ErrorID::Success, arr);
		}

		void FHostSpWrapper::AbortSequence()
		{
			HRESULT  hr = m_Process->AbortSequence(_bstr_t(m_WorkspacePath.c_str()));
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPAbortSequence, Util::ErrorID::ErrorFHostSPAbortFailed, "");
                return;
            }
            Sleep(500);
			emit NewMessage(Util::Functions::FHostSPAbortSequence, Util::ErrorID::Success, "");
		}


		void FHostSpWrapper::LoadSequence(const QFile &Flashfile)
		{
            if (!Flashfile.exists())
            {
				emit NewMessage(Util::Functions::FHostSPLoadFlashFile, Util::ErrorID::ErrorFHostSPFlashfileNotExits, "");
                return;
            }

            QFileInfo f = QFileInfo(Flashfile);
			QString filename = f.absoluteFilePath().replace(PRG_POSTFIX, CFX_POSTFIX);
            m_WorkspacePath = f.absoluteFilePath().toStdString();
            if (!QFile(filename).exists())
            {
				emit NewMessage(Util::Functions::FHostSPLoadFlashFile, Util::ErrorID::ErrorFHostSPFlashfileNotExits, "");
                return;
            }

            HRESULT  hr = m_Process->LoadSequence(_bstr_t(f.absoluteFilePath().toStdString().c_str()), _bstr_t(filename.toStdString().c_str()), _bstr_t("Test"));
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPLoadFlashFile, Util::ErrorID::ErrorFHostSPLoadFlashfileFailed, "");
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
				emit NewMessage(Util::Functions::FHostSPLoadFlashFile, Util::ErrorID::Success, "");
                return;
			}
            Sleep(100);
			emit NewMessage(Util::Functions::FHostSPLoadFlashFile, Util::ErrorID::ErrorFHostSPLoadFlashfileStatusFailed, "");
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
            //Safty Sleep
            QThread::msleep(5000);
			//! \todo  Hier sollte der Pfad aus der Konfiguration gelesen werden
			HRESULT  hr = m_Process->StartSequence(_bstr_t(m_WorkspacePath.c_str()), _bstr_t("C:\\Program Files (x86)\\FHostSP\\FHostSP.cfx"));
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::FHostSPStartFlash, Util::ErrorID::ErrorFHostSPSequenceStart, "");
                return;
            }
            Sleep(100);
			emit NewMessage(Util::Functions::FHostSPStartFlash, Util::ErrorID::Success, "");
		}

	}
}