#include "ShutdownHandler.hpp"


namespace RW{
	namespace CORE{

			namespace HW{
	
	}

		ShutdownHandler::ShutdownHandler(QObject *Parent) : BasicWrapper(Parent),
			m_ShutdownTimer(nullptr),
			m_Timeout(0)
		{
		}

		void ShutdownHandler::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
		{
			if (Type == Util::MessageReceiver::ShutdownHandler)
			{
				switch (Func)
				{
				case RW::CORE::Util::Functions::StartShutdownTimer:
				{
					StartShutdownTimer(Report.toLong());
				}
				break;
				case RW::CORE::Util::Functions::StopShutdownTimer:
				{
					StopShutdownTimer();
				}
				break;
				default:
					break;
				}
			}
		}


		ShutdownHandler::~ShutdownHandler()
		{
		}

		void ShutdownHandler::StartShutdownTimer(quint64 Time)
		{
			if (m_ShutdownTimer == nullptr)
			{
				m_ShutdownTimer = new QTimer(this);
			}
			connect(m_ShutdownTimer, &QTimer::timeout, this, &ShutdownHandler::Shutdown);
			m_ShutdownTimer->start(Time);
			//m_logger->debug("Shutdown timger started","RemoteHiddenHelper");
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		void ShutdownHandler::StopShutdownTimer()
		{
			if (m_ShutdownTimer != nullptr && m_ShutdownTimer->isActive())
			{
				m_ShutdownTimer->stop();
				//m_logger->debug("Shutdown timer stopped.");
			}
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		void ShutdownHandler::Shutdown()
		{

#ifdef DEBUG_WITHOUT_SHUTDOWN
			//This is for testing propes of the shutdown mechanism. 
			//After the execution of this statment the mechanism is broken because we wont get back in initial state without restart.
			m_logger->debug("ShutdownHandler: PC shutdown");
			m_ShutdownTimer->stop();
			emit ShutdownEvt();
#else
			if (ShutdownByWinApi())
			{
				m_ShutdownTimer->stop();
				emit ShutdownEvt();
				//m_logger->debug("ShutdownHandler: PC shutdown");
			}
			else
			{
				//m_logger->debug("ShutdownHandler: PC don't shutdown");
			}
#endif // DEBUG
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		/*
		@brief Shutdown the RemoteWorkstation.
		@note This funktion has no influence of the connected hardware.
		@return
		*/
		bool ShutdownHandler::ShutdownByWinApi()
		{
			HANDLE hToken = NULL;
			TOKEN_PRIVILEGES tkp = { 0 };
			bool bRet = false;

			// Get a token for this process. 
			if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
				if (LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) {
					tkp.PrivilegeCount = 1;  // one privilege to set    
					tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

					// Get the shutdown privilege for this process. 
					if (AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0)) {
						::CloseHandle(hToken);

						if (ERROR_SUCCESS == GetLastError()) {

							DWORD dwFlags = EWX_POWEROFF;
							DWORD dwReason = SHTDN_REASON_MAJOR_SYSTEM;

							if (ExitWindowsEx(dwFlags, dwReason)) {
								bRet = true;
							}
						}
					}
				}
			}

			return bRet;
		}

	}
}