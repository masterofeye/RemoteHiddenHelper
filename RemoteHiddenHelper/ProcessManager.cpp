#include "ProcessManager.h"
#include "CanEasyWrapper.h"
#include "FHostSpWrapper.h"
#include "MKSWrapper.h"
#include "PortalInfo.h"
#include "ErrorHandler.h"
#include "FileUtils.h"
#include "UsbHidLoader.h"
#include "Inactivitywatcher.h"
#include "RemoteDataConnectLibrary.h"
#include "MessageWrapper.h"
#include "ExitHandler.h"
#include <QDatastream>


namespace RW{
	namespace CORE{



        ProcessManager::ProcessManager(QObject* Parent) : QObject(Parent),
            m_Logger(spdlog::get("file_logger")),
            m_CanEasy(new CanEasyWrapper(this)),
            m_FHostSP(new FHostSpWrapper(this)),
            m_PortalInfo(new PortalInfo(this)),
            m_MKS(new MKSWrapper(this)),
            m_FileUtils(new FileUtils(this)),
            m_ErrorHandler(new ErrorHandler(this)),
            m_UsbHidLoader(new UsbHidLoader(this)),
            m_InactivityWatcher(new InactivityWatcher(this)),
            m_MessageWrapper(new MessageWrapper(this)),
            m_ExitHandler(new ExitHandler(this))
		{
			m_CommunicationServer = new COM::CommunicatonServer(false, COM::TypeofServer::RemoteHiddenHelper, "Server", 1234, m_Logger, this);
            
			m_CommunicationServer->Register(m_CanEasy);
			m_CommunicationServer->Register(m_FHostSP);
			m_CommunicationServer->Register(m_MKS);
			m_CommunicationServer->Register(m_PortalInfo);
			m_CommunicationServer->Register(m_FileUtils);
			m_CommunicationServer->Register(m_UsbHidLoader);
			m_CommunicationServer->Register(m_InactivityWatcher);
            m_CommunicationServer->Register(m_MessageWrapper);
            /*Muss nach m_InactivityWatcher registriert werden*/
            m_CommunicationServer->Register(m_ExitHandler);
            m_CommunicationServer->Register(this);


			//...danach erhält der Errorhandler die Informationen (Reihenfolge der Signal/Slot Verbindung)
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FileUtils, &FileUtils::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_UsbHidLoader, &UsbHidLoader::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_InactivityWatcher, &InactivityWatcher::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_MessageWrapper, &MessageWrapper::OnProcessMessage, Qt::DirectConnection);

			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_FileUtils, &FileUtils::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_UsbHidLoader, &UsbHidLoader::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_InactivityWatcher, &InactivityWatcher::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_MessageWrapper, &MessageWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			m_Logger->flush();

         

            m_CommunicationServer->ListenJustLocal();
		}


		ProcessManager::~ProcessManager()
		{
            m_Logger->flush();
		}

        void ProcessManager::OnProcessMessage(COM::Message Msg)
        {
            switch (Msg.MessageID())
            {
                //Resetet die Checkbox für den Permanent Login
                case COM::MessageDescription::EX_PermanentLogin:
                {
                    if (!Msg.IsProcessed())
                    {
                        QList<QVariant> list = Msg.ParameterList();
                        bool isPermanent = list.first().toBool();
                        if (!isPermanent)
                            emit ResetPermanentCheckBox();
                    }
                }
                break;
                //Wir müssen garantieren, dass die Checkbox im Tray richtig initialisiert wird
                case COM::MessageDescription::EX_StartInactivityTimer: 
                    if (!Msg.IsProcessed())
                    {
                        QList<QVariant> list = Msg.ParameterList();
                        //Extrakt das Permanent Login Flag
                        emit CheckPermanentCheckBox(list[5].toBool());
                    }
                break;
            default:
                break;
            }
        }



	}
}
