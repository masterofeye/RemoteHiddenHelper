#include "CommunicationManager.h"
#include "CommunicationServer.h"

#include "ErrorHandler.h"
#include "Util.h"

namespace RW{
	namespace CORE{
        CommunicationManager::CommunicationManager(ErrorHandler* ErrorHandler, QObject* Parent) : QObject(Parent),
			m_Server(new CommunicationServer(this)),
            m_ErrorHandler(ErrorHandler)
		{
			connect(m_Server, &CommunicationServer::NewMessage, this, &CommunicationManager::OnProcessMessage);
            connect(this, &CommunicationManager::NewMessage, m_Server, &CommunicationServer::OnProcessMessage);
			m_Server->Init();
		}

		CommunicationManager::~CommunicationManager()
		{
			m_Server->DeInit();
		}

		void CommunicationManager::OnProcessMessage(Util::Functions MessageType, QByteArray Message)
		{
			switch (MessageType)
			{
			case Util::Functions::CanEasyStartApplication:
				if (m_ErrorHandler->IsBusy(Util::MessageReceiver::CanEasyWrapper))
                {
					emit NewMessage(Util::MessageReceiver::CommunicationServer, MessageType, CreateMessage(MessageType, "", Util::ErrorID::Busy));
                }
                else
                {
					emit NewMessage(Util::MessageReceiver::CanEasyWrapper, MessageType, Message);
                }
				break;
            case Util::Functions::CanEasyLoadWorkspace:
            {
				emit NewMessage(Util::MessageReceiver::CanEasyWrapper, MessageType, Message);
                break;
            }
            case Util::Functions::CanEasyStartSimulation:
				emit NewMessage(Util::MessageReceiver::CanEasyWrapper, MessageType, Message);
                break;
            case Util::Functions::CanEasyStopSimulation:
				emit NewMessage(Util::MessageReceiver::CanEasyWrapper, MessageType, Message);
                break;
			case Util::Functions::CanEasyCloseApplication:
				emit NewMessage(Util::MessageReceiver::CanEasyWrapper, MessageType, Message);
				break;
			case Util::Functions::MKSLogin:
				if (m_ErrorHandler->IsBusy(Util::MessageReceiver::MKSWrapper))
                {
					emit NewMessage(Util::MessageReceiver::CommunicationServer, MessageType, CreateMessage(MessageType, "", Util::ErrorID::Busy));
                }
                else
                {
					emit NewMessage(Util::MessageReceiver::MKSWrapper, MessageType, Message);
                }
				break;
			case Util::Functions::MKSStartDownload:
				emit NewMessage(Util::MessageReceiver::MKSWrapper, MessageType, Message);
				break;
			case Util::Functions::MKSCreateSandBox:
				emit NewMessage(Util::MessageReceiver::MKSWrapper, MessageType, Message);
				break;
			case Util::Functions::MKSDropSandbox:
				emit NewMessage(Util::MessageReceiver::MKSWrapper, MessageType, Message);
				break;
            case Util::Functions::FHostSPStartFHost:
				if (m_ErrorHandler->IsBusy(Util::MessageReceiver::FHostSPWrapper))
                {
					emit NewMessage(Util::MessageReceiver::CommunicationServer, MessageType, CreateMessage(MessageType, "", Util::ErrorID::Busy));
                }
                else
                {
					emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
                }
                break;
			case Util::Functions::FHostSPCloseFHost:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
				break;
            case Util::Functions::FHostSPCloseSequence:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
                break;
			case Util::Functions::FHostSPLoadFlashFile:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
				break;
			case Util::Functions::FHostSPStartFlash:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
				break;
            case Util::Functions::FHostSPAbortSequence:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
                break;
            case Util::Functions::FHostSPGetProgress:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
                break;
            case Util::Functions::FHostSPGetState:
				emit NewMessage(Util::MessageReceiver::FHostSPWrapper, MessageType, Message);
                break;
            case Util::Functions::PortalInfoShowDialog:
				if (m_ErrorHandler->IsBusy(Util::MessageReceiver::PortalInfo))
				{
					emit NewMessage(Util::MessageReceiver::CommunicationServer, MessageType, CreateMessage(MessageType, "", Util::ErrorID::Busy));
				}
				else
				{
					emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
				}
				break;
                break;
            case Util::Functions::PortalInfoCloseDialog:
                emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
                break;
            case Util::Functions::PortalInfoFittingAC:
                emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
                break;
            case Util::Functions::PortalInfoAcByIcom:
                emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
                break;
            case Util::Functions::PortalInfoReleases:
                emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
                break;
            case Util::Functions::PortalInfoSoftwareById:
                emit NewMessage(Util::MessageReceiver::PortalInfo, MessageType, Message);
                break;
            case Util::Functions::FileUtilUnZip :
                emit NewMessage(Util::MessageReceiver::FileUtil, MessageType, Message);
                break;
            case Util::Functions::FileUtilDelete:
                emit NewMessage(Util::MessageReceiver::FileUtil, MessageType, Message);
                break;
            case Util::Functions::UsbHidLoaderFlashFile:
                emit NewMessage(Util::MessageReceiver::UsbHidLoader, MessageType, Message);
                break;
			case Util::Functions::StartShutdownTimer:
				emit NewMessage(Util::MessageReceiver::ShutdownHandler, MessageType, Message);
				break;
			case Util::Functions::StopShutdownTimer:
				emit NewMessage(Util::MessageReceiver::ShutdownHandler, MessageType, Message);
				break;
			case Util::Functions::StartInactivityTimer:
				emit NewMessage(Util::MessageReceiver::InactivityWatcher, MessageType, Message);
				break;
			case Util::Functions::StopInactivityTimer:
				emit NewMessage(Util::MessageReceiver::InactivityWatcher, MessageType, Message);
				break;
			default:
				break;
			}
		}

		/*******************************************************************//**
		@autor Ivo Kunadt
		@brief Empfängt die NewMessageAnswer Signale von den Module und leitet sie an den CommunicationServer weiter.
		@param Func Aktuell verarbeiteter Arbeitsschritt.
		@param Id Fehlercode falls der Arbeitsschritt nicht erfolgreich abgeschlossen wurde.
		@param Message Zusätzliche User Daten für den Service
		@return void
		********************************************************************************************************************/
		void CommunicationManager::OnProcessMessageAnswer(Util::Functions Func, Util::ErrorID Id, QByteArray Message)
        {
			//Message Daten in die Message Struktur packen
            QByteArray arr;
			RW::CORE::Message m(Func, Message.size(), Message, Id);
            QDataStream in(&arr, QIODevice::WriteOnly);
            in.setVersion(QDataStream::Qt_5_7);
            in << m;

			//Nachricht nun an den CommunicationServer weiterleiten
			emit NewMessage(Util::MessageReceiver::CommunicationServer, Func, arr);

        }

		QByteArray CommunicationManager::CreateMessage(Util::Functions Func, QByteArray Message, Util::ErrorID Id)
        {
            QByteArray arr;
            RW::CORE::Message m(Func, Message.size(), Message, Id);
            QDataStream in(&arr, QIODevice::WriteOnly);
            in.setVersion(QDataStream::Qt_5_7);
            in << m;
            return arr;
        }
	}
}