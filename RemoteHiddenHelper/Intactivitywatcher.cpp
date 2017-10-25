#include "inactivitywatcher.h"
#include <QLibrary>
#include <qdatastream.h>
#include <windows.h>
#include <Wtsapi32.h>
#include <userenv.h>
#include <windows.h> 

#include "RemoteDataConnectLibrary.h"


#pragma comment(lib, "wtsapi32.lib")
#pragma comment(lib, "userenv.lib")


namespace RW{
	namespace CORE{

		InactivityWatcher::InactivityWatcher(QObject *parent) : BasicWrapper(parent),
			m_TimerLogout(nullptr),
			m_Timeout(0),
            m_WorkstationType(WorkstationKind::RemoteWorkstation),
            m_IsPermanent(false),
            m_PermamentTimout(false),
            m_logger(spdlog::get("file_logger"))
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
                    m_LogoutTimeStart = Msg.ParameterList()[2].toTime();
                    m_LogoutTimeEnd = Msg.ParameterList()[3].toTime();
                    m_WorkstationType = Msg.ParameterList()[4].value<WorkstationKind>();
                    m_IsPermanent = Msg.ParameterList()[5].toBool();
                    m_MaxPermanentLoginTime = Msg.ParameterList()[6].toDateTime();
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
            case COM::MessageDescription::EX_PermanentLogin:
            {
                if (!Msg.IsProcessed())
                {
                    QList<QVariant> list = Msg.ParameterList();
                    m_IsPermanent = list.first().toBool();
                    
                    if (m_PermamentTimout == nullptr)
                    {
                        m_PermamentTimout = new QTimer(this);
                        connect(m_PermamentTimout, &QTimer::timeout, this, &InactivityWatcher::OnPermanetLoginEnd);
                        
                        QDateTime t = QDateTime::currentDateTime();
                        quint64 timediff = t.msecsTo(m_MaxPermanentLoginTime);

                        m_PermamentTimout->start(timediff);
                        m_logger->info("Permanent Login activated", (int)spdlog::sinks::FilterType::PermanentLoginState);
                    }
                    else
                    {
                        m_PermamentTimout->stop();
                        delete m_PermamentTimout;
                        m_PermamentTimout = nullptr;
                        m_logger->info("Permanent Login deactivated", (int)spdlog::sinks::FilterType::PermanentLoginState);
                    }
                }
            }
			break;
			default:
				break;
			}
		}

        void InactivityWatcher::OnPermanetLoginEnd()
        {
            m_IsPermanent = false;
            COM::Message m;
            m.SetMessageID(COM::MessageDescription::EX_PermanentLogin);
            m.SetIsExternal(true);
            m.setIdentifier(m.GenUUID(COM::TypeofServer::RemoteHiddenHelper).toString());
            QList<QVariant> list;
            list.append(m_IsPermanent);
            m.SetParameterList(list);
            emit NewMessage(m);
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

            QTime currentTime = QTime::currentTime();
            if (((m_LogoutTimeStart > currentTime || currentTime > m_LogoutTimeEnd) 
                || m_WorkstationType==WorkstationKind::RemoteWorkstation)
                && !m_IsPermanent)
            {
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
                        /*!Wir senden eine Bestätigungsmessage schon hier ab. Wenn es zu einem Fehler
                        kommt wird noch eine Negative message hinterher geschickt.
                        Hintergrund ist das Logoff sofort dafür sorgt, das der RemoteHiddenhelper geschlossen wird.
                        */
                        msg.SetSuccess(true);
                        emit NewMessage(msg);
                        emit LogOff(sessionId);
                    }
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
                /*!Wir senden eine Bestätigungsmessage schon hier ab. Wenn es zu einem Fehler 
                kommt wird noch eine Negative message hinterher geschickt.
                Hintergrund ist das Logoff sofort dafür sorgt, das der RemoteHiddenhelper geschlossen wird.
                */

                msg.SetSuccess(true);
                emit NewMessage(msg);
                emit LogOff(sessionId);
            }
        }


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
                    if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, wts.SessionId, WTS_INFO_CLASS::WTSUserName, &buffer, &bufferSize))
                    {
                        QString username = QString::fromWCharArray(buffer, bufferSize);
                        WTSFreeMemory(buffer);
                        if (Username.isEmpty())
                            m_logger->warn("Username is empty.");
                        int res = 0;

                        QString var1 = username.trimmed().toUtf8().toUpper();
                        QString var2 = Username.trimmed().toUtf8().toUpper();

                        if ((res = QString::compare(var1, var2, Qt::CaseInsensitive)) == 0)
                        {
                            SessioNumber = wts.SessionId;
                            break;
                        }
                        m_logger->flush();
                    }
                }
                WTSFreeMemory(pSessionsBuffer);
                return true;
            }
            else
            {
                DWORD err = GetLastError();
                m_logger->error("WTSEnumerateSessions failed. GetLastError: {}", err);
                return false;
            }
        }

    }
}