#include "inactivitywatcher.h"
#include <windows.h>
#include <QLibrary>

#include <Wtsapi32.h>
#include <userenv.h>
#include <windows.h> 
#include <qdatastream.h>

#pragma comment(lib, "wtsapi32.lib")
#pragma comment(lib, "userenv.lib")


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
            connect(this, &InactivityWatcher::LogOff, this, &InactivityWatcher::OnLogOff);
		}

		void InactivityWatcher::OnProcessMessage(COM::Message Msg)
		{
			switch (Msg.MessageID())
			{
			case COM::MessageDescription::EX_StartInactivityTimer:
			{
                if (!Msg.IsProcessed())
                {
                    m_Timeout = Msg.ParameterList()[0].toLongLong();
					m_UserName = Msg.ParameterList()[1].toString();
                    StartInactivityObservation();
                }
			}
			break;
			case COM::MessageDescription::EX_StopInactivityTimer:
            {                
                if (!Msg.IsProcessed())
                {
                    StopInactivityObservation();
                }
			}
            break;
            case COM::MessageDescription::EX_LogoutImmediately:
            {
                if (!Msg.IsProcessed())
                {
                    LogOutUser();
                }
            }
			break;
			default:
				break;
			}
		}


		uint InactivityWatcher::GetLastInputTime()
		{
			LASTINPUTINFO li;
			li.cbSize = sizeof(LASTINPUTINFO);
			::GetLastInputInfo(&li);

			DWORD te = ::GetTickCount();
			float elapsed = (te - li.dwTime);
			return elapsed;
		}

		void InactivityWatcher::StartInactivityObservation()
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_StartInactivityTimer);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			if (m_TimerLogout == nullptr)
			{
				m_TimerLogout = new QTimer(this);
			}
            connect(m_TimerLogout, &QTimer::timeout, this, &InactivityWatcher::LogOutUserByTimer);

			//m_TimerLogout->setSingleShot(true);
			m_TimerLogout->start(5000);
			Sleep(100);
			//qApp->processEvents();
            msg.SetSuccess(true);
            msg.SetIsProcessed(true);
            emit NewMessage(msg);
		}

		void InactivityWatcher::StopInactivityObservation()
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_StopInactivityTimer);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			if (m_TimerLogout != nullptr && m_TimerLogout->isActive())
			{
				m_TimerLogout->stop();
                msg.SetSuccess(true);
                msg.SetIsProcessed(true);
                emit NewMessage(msg);
			}
#ifdef DEBUG
			m_logger->flush();
#endif // DEBUG
		}

		
        void InactivityWatcher::LogOutUserByTimer()
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_ProcessLogout);
            msg.SetIsProcessed(true);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            //m_logger->debug("LogoutUser was called.");
            if (GetLastInputTime() >= m_Timeout)
            {
                m_TimerLogout->stop();

                quint64 sessionId = 0;
				if (!QueryActiveSession(sessionId, m_UserName))
                {
                    msg.SetSuccess(false);
                    emit NewMessage(msg);
                }
                else
                {
                    /*Wir senden eine Bestätigungsmessage schon hier ab. Wenn es zu einem Fehler
                    kommt wird noch eine Negative message hinterher geschickt.
                    Hintergrund ist das Logoff sofort dafür sorgt, das der RemoteHiddenhelper geschlossen wird.
                    */
                    msg.SetSuccess(true);
                    emit NewMessage(msg);
                    emit LogOff(sessionId);
                }
            }
		}

        void InactivityWatcher::LogOutUser()
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_ProcessLogout);
            msg.SetIsProcessed(true);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            quint64 sessionId = 0;
			if (!QueryActiveSession(sessionId, m_UserName))
            {
                msg.SetSuccess(false);
                emit NewMessage(msg);
            }
            else
            {
                /*Wir senden eine Bestätigungsmessage schon hier ab. Wenn es zu einem Fehler 
                kommt wird noch eine Negative message hinterher geschickt.
                Hintergrund ist das Logoff sofort dafür sorgt, das der RemoteHiddenhelper geschlossen wird.
                */
                msg.SetSuccess(true);
                emit NewMessage(msg);
                emit LogOff(sessionId);
            }
        }

		/*
		@brief Logs off the current user from the active session. It is irelevant, if it is a console or rdp session.
		It needs the session number, which can be queried with the QueryActiveSession method.
		@param SessioNumber The session number to the current active session.
		@return
		*/
        void InactivityWatcher::OnLogOff(quint64 SessioNumber)
        {
            quint16 error = 0;
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_ProcessLogout);
            msg.SetIsProcessed(true);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
			if (!WTSLogoffSession(WTS_CURRENT_SERVER_HANDLE, SessioNumber, true))
			{
                error = GetLastError();
                msg.SetSuccess(false);
                msg.SetResult(error);
                emit NewMessage(msg);
				return;
			}
			else
			{
				//This will be logged by the service. No logging needed here.
				return;
			}

		}

        /*
        *@brief Returns the session number, that is currently in state active.
        *@return True if a session was in the active state
        */
        bool InactivityWatcher::QueryActiveSession(quint64 &SessioNumber, QString Username)
        {
            SessioNumber = 0;
            PWTS_SESSION_INFO  pSessionsBuffer = NULL;
            DWORD dwSessionCount = 0;
            WTS_SESSION_INFO  wts;
            WTS_INFO_CLASS wic;
            m_logger = spdlog::get("file_logger");

            if (WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSessionsBuffer, &dwSessionCount))
            {
                //Loop through all Sessions
                for (quint8 i = 0; i < dwSessionCount; i++)
                {
                    wts = pSessionsBuffer[i];
					DWORD bufferSize = 0;
					LPWSTR buffer ;
					WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, wts.SessionId, WTS_INFO_CLASS::WTSUserName, &buffer, &bufferSize);
					QString username = QString::fromWCharArray(buffer, bufferSize);

					if (m_UserName.isEmpty())
						m_logger->warn("Username is empty.");

					if (username.toUpper() == m_UserName.toUpper())
					{
						SessioNumber = wts.SessionId;
						m_logger->debug("SessionNumber is: {}", SessioNumber);
						return true;
					}
					WTSFreeMemory(buffer);
                }
				WTSFreeMemory(pSessionsBuffer);
            }
            else
            {
                DWORD err = GetLastError();
                m_logger->error("WTSEnumerateSessions failed. GetLastError: {}", err);
                return false;
            }
			return false;
        }

    }
}