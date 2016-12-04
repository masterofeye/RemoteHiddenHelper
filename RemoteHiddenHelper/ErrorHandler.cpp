#include "ErrorHandler.h"
#include "Util.h"
#include "qdebug.h"

namespace RW{
    namespace CORE
    {
        ErrorHandler::ErrorHandler(QObject* Parent) : QObject(Parent), 
            m_IsCanEasyRunning(false),
            m_IsFHostSPRunning(false),
            m_IsMKSRunning(false),
			m_IsPortalInfoRunning(false)
        {
        }

        ErrorHandler::~ErrorHandler()
        {
        }

        void ErrorHandler::PrintDebugInformation()
        {
            qDebug() << "###################################";
            qDebug() << "Is CanEasy running " << m_IsCanEasyRunning;
            qDebug() << "Is MKS running " << m_IsMKSRunning;
            qDebug() << "Is FHostSP running " << m_IsFHostSPRunning;
			qDebug() << "Is PortalInfo running " << m_IsPortalInfoRunning;
            qDebug() << "Is ErrorHandler busy" << IsBusy();
            qDebug() << "###################################";
        }

		void ErrorHandler::OnProcessMessageAnswer(Util::Functions Func, Util::ErrorID Id, QByteArray Message)
        {
            //Message Daten in die Message Struktur packen
            QByteArray arr;
            RW::CORE::Message m(Func, Message.size(), Message, Id);

            switch (Func)
            {
            case Util::Functions::CanEasyStartApplication:
                //Wenn CanEasy gestartet wurde dann Flag setzen
				if (Id == Util::ErrorID::Success)
                {
                    m_IsCanEasyRunning = true;
                    break;
                }
            case Util::Functions::CanEasyLoadWorkspace:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::CanEasyStartSimulation:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::CanEasyStopSimulation:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::CanEasyCloseApplication:
                //Wenn CanEasy gestoppt wurde denn Flag wieder löschen. Wenn es allerdings zu einem Fehler gekommen ist soll CanEasy geschlossen werden.
				if (Id == Util::ErrorID::Success)
                {
                    m_IsCanEasyRunning = false;
                    break;
                }
				else
				{
					emit NewMessage(Util::MessageReceiver::CanEasyWrapper, Util::Functions::CanEasyCloseApplication, "");
					if (m_IsMKSRunning)
					{
						//Als letzes wird der Dialog geschlossen und beendet die Applikation
						emit NewMessage(Util::MessageReceiver::MKSWrapper, Util::Functions::MKSClose, "");
					}

					if (m_IsPortalInfoRunning)
					{
						//Als letzes wird der Dialog geschlossen und beendet die Applikation
						emit NewMessage(Util::MessageReceiver::PortalInfo, Util::Functions::PortalInfoCloseDialog, "");
					}
				}
                break;
            case Util::Functions::MKSLogin:
				if (Id == Util::ErrorID::Success)
                    m_IsMKSRunning = true;
                break;
            case Util::Functions::MKSStartDownload:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::MKSCreateSandBox:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::MKSDropSandbox:
				if (Id == Util::ErrorID::Success)
					break;
			case Util::Functions::MKSClose:
				if (Id == Util::ErrorID::Success)
					m_IsMKSRunning = false;
				else
				{
					emit NewMessage(Util::MessageReceiver::MKSWrapper, Util::Functions::MKSClose, "");
					if (m_IsPortalInfoRunning)
					{
						//Als letzes wird der Dialog geschlossen und beendet die Applikation
						emit NewMessage(Util::MessageReceiver::PortalInfo, Util::Functions::PortalInfoCloseDialog, "");
					}
				}

            case Util::Functions::FHostSPStartFHost:
                //Wenn CanEasy gestartet wurde dann Flag setzen
				if (Id == Util::ErrorID::Success)
                {
                    m_IsFHostSPRunning = true;
                    break;
                }
            case Util::Functions::FHostSPLoadFlashFile:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPStartFlash:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPGetState:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPGetProgress:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPAbortSequence:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPCloseSequence:
				if (Id == Util::ErrorID::Success)
                    break;
            case Util::Functions::FHostSPCloseFHost:
				if (Id == Util::ErrorID::Success)
				{
					m_IsFHostSPRunning = false;
					break;
				}
                else
                {
					emit NewMessage(Util::MessageReceiver::FHostSPWrapper, Util::Functions::FHostSPAbortSequence, "");
					emit NewMessage(Util::MessageReceiver::FHostSPWrapper, Util::Functions::FHostSPCloseSequence, "");
					emit NewMessage(Util::MessageReceiver::FHostSPWrapper, Util::Functions::FHostSPCloseFHost, "");
					if (m_IsMKSRunning)
					{
						//Als letzes wird der Dialog geschlossen und beendet die Applikation
						emit NewMessage(Util::MessageReceiver::MKSWrapper, Util::Functions::MKSClose, "");
					}
                    if (m_IsCanEasyRunning)
                    {
						emit NewMessage(Util::MessageReceiver::CanEasyWrapper, Util::Functions::CanEasyCloseApplication, "");;
                    }
					if (m_IsPortalInfoRunning)
					{
						//Als letzes wird der Dialog geschlossen und beendet die Applikation
						emit NewMessage(Util::MessageReceiver::PortalInfo, Util::Functions::PortalInfoCloseDialog, "");
					}
                }
				break;
			case Util::Functions::PortalInfoShowDialog:
				if (Id == Util::ErrorID::Success)
					m_IsPortalInfoRunning = true;
				break;
			case Util::Functions::PortalInfoCloseDialog:
				if (Id == Util::ErrorID::Success)
				{
					m_IsPortalInfoRunning = false;
				}
				else
				{
					//Nur PortalInfo sollte laufen, alles andere ist noch nicht gestartet. Somit müssen wir nur den Dialog beenden, was zeitgleich die gesamte Applikation stoppt
					emit NewMessage(Util::MessageReceiver::PortalInfo, Util::Functions::PortalInfoCloseDialog, "");
				}
                break;
            default:
                break;
            }
            PrintDebugInformation();

        }
    }
}

