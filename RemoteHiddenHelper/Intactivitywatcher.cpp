#include "inactivitywatcher.hpp"
#include <windows.h>
#include <QLibrary>

#include <Wtsapi32.h>
#include <userenv.h>
#include <windows.h> 

#pragma comment(lib, "wtsapi32.lib")
#pragma comment(lib, "userenv.lib")

#if defined(DEBUG) && defined(DEBUG_WITHOUT_LOGOUT)
	#define DEFAULT_TIMEOUT 60*60
#elif defined(DEBUG)
	#define DEFAULT_TIMEOUT 60*60*1000
#else
	#define DEFAULT_TIMEOUT 1000*60*180
#endif

namespace RW{
	namespace CORE{

		/*
		@brief
		@param Version Specified the configuration version for the DB query.
		
		*/
		InactivityWatcher::InactivityWatcher(QObject *parent) : BasicWrapper(parent),
			m_TimerLogout(nullptr),
			m_Timeout(0)
		{
		}

		void InactivityWatcher::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
		{
			if (Type == Util::MessageReceiver::InactivityWatcher)
			{
				switch (Func)
				{
				case RW::CORE::Util::Functions::StartInactivityTimer:
				{
					StartInactivityObservation(Report.toLong());
				}
				break;
				case RW::CORE::Util::Functions::StopInactivityTimer:
				{
					StopInactivityObservation();
				}
				break;
				default:
					break;
				}
			}
		}


		uint InactivityWatcher::GetLastInputTime()
		{
			LASTINPUTINFO li;
			li.cbSize = sizeof(LASTINPUTINFO);
			::GetLastInputInfo(&li);

			DWORD te = ::GetTickCount();
			float elapsed = (te - li.dwTime) / 100.0;
			return elapsed;
		}

		void InactivityWatcher::StartInactivityObservation(quint64 Time)
		{
			
			if (m_TimerLogout == nullptr)
			{
				m_TimerLogout = new QTimer(this);
			}
			connect(m_TimerLogout, &QTimer::timeout, this, &InactivityWatcher::LogOutUser);
			//m_TimerLogout->setSingleShot(true);
			m_TimerLogout->start(5000);
			Sleep(100);
			//qApp->processEvents();
			
		}

		void InactivityWatcher::StopInactivityObservation()
		{
			if (m_TimerLogout != nullptr && m_TimerLogout->isActive())
			{
				m_TimerLogout->stop();
				//m_logger->debug("Inactivitity Timer stopped.");
			}
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		
		void InactivityWatcher::LogOutUser()
		{
			//m_logger->debug("LogoutUser was called.");
			if (GetLastInputTime() >= m_Timeout)
			{
#ifdef DEBUG_WITHOUT_LOGOUT
				m_TimerLogout->stop();
				m_logger->debug("User is logged out now.");
				m_logger->flush();

				emit UserInactive();
#else
				quint64 sessionId = 0;
				if (!QueryActiveSession(sessionId))
				{
					//m_logger->error("Log-off of user failed.");

				}
				else
				{
					if (LogOff(sessionId))
					{
						m_TimerLogout->stop();
						//m_logger->info("User is logged out now.");
						//m_logger->flush();
						emit UserInactive();
					}
					else
					{
						//m_logger->error("Log-off of user failed.");
					}
				}
#endif // DEBUG
			}
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		/*
		@brief Logs off the current user from the active session. It is irelevant, if it is a console or rdp session.
		It needs the session number, which can be queried with the QueryActiveSession method.
		@param SessioNumber The session number to the current active session.
		@return
		*/
		bool InactivityWatcher::LogOff(quint64 SessioNumber)
		{
			if (!WTSLogoffSession(WTS_CURRENT_SERVER_HANDLE, SessioNumber, true))
			{
				DWORD err = GetLastError();
				//m_logger->error("WTSLogoffSession failed. GetLastError: ");// << err;
				return false;
			}
			else
			{
				//This will be logged by the service. No logging needed here.
				return true;
			}
		}

		/*
		*@brief Returns the session number, that is currently in state active.
		*@return True if a session was in the active state
		*/
		bool InactivityWatcher::QueryActiveSession(quint64 &SessioNumber)
		{
			SessioNumber = 0;
			PWTS_SESSION_INFO  pSessionsBuffer = NULL;
			DWORD dwSessionCount = 0;
			WTS_SESSION_INFO  wts;

			if (WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSessionsBuffer, &dwSessionCount))
			{
				//Loop through all Sessions
				for (quint8 i = 0; i < dwSessionCount; i++)
				{
					wts = pSessionsBuffer[i];
					//Nur aktive Sessions weden berücksichtigt
					if (wts.State == WTSActive)
					{
						SessioNumber = wts.SessionId;
						//m_logger->debug("SessionNumber is: ");// << SessioNumber;
					}
				}
				return true;
			}
			else
			{
				DWORD err = GetLastError();
				//m_logger->error("WTSEnumerateSessions failed. GetLastError: ");// << err;
				return false;
			}
		}

	}
}