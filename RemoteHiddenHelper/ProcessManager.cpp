#include "ProcessManager.h"
#include "CanEasyWrapper.h"
#include "FHostSpWrapper.h"
#include "MKSWrapper.h"
#include "PortalInfo.h"
#include "ErrorHandler.h"
#include "FileUtils.h"
#include "UsbHidLoader.h"
#include "Inactivitywatcher.hpp"
#include "RemoteDataConnectLibrary.h"



namespace RW{
	namespace CORE{

		ProcessManager::ProcessManager(QObject* Parent) : QObject(Parent),
			m_CanEasy(new CanEasyWrapper(this)),
			m_FHostSP(new FHostSpWrapper(this)),
			m_PortalInfo(new PortalInfo(this)),
			m_MKS(new MKSWrapper(this)),
            m_FileUtils(new FileUtils(this)),
            m_ErrorHandler(new ErrorHandler(this)),
            m_UsbHidLoader(new UsbHidLoader(this)),
			m_InactivityWatcher(new InactivityWatcher(this))
		{
			m_logger = spdlog::get("file_logger");
			if (m_logger == nullptr)
			{
				m_logger = spdlog::create<spdlog::sinks::MySqlSink>("file_logger");
			}
			m_logger->set_pattern("[%H:%M:%S:%f] [%g] [%l] [thread %t] %v ");
#ifdef REMOTESERVICE_DEBUG
			m_logger->set_level(spdlog::level::debug);
#else
			m_logger->set_level(spdlog::level::info);
#endif 
			m_logger->set_type(1);


			m_CommunicationServer = new COM::CommunicatonServer(false, "Server", 1234, m_logger, this);


			m_CommunicationServer->Register(m_CanEasy);
			m_CommunicationServer->Register(m_FHostSP);
			m_CommunicationServer->Register(m_MKS);
			m_CommunicationServer->Register(m_PortalInfo);
			m_CommunicationServer->Register(m_FileUtils);
			m_CommunicationServer->Register(m_UsbHidLoader);
			m_CommunicationServer->Register(m_InactivityWatcher);


			//...danach erhält der Errorhandler die Informationen (Reihenfolge der Signal/Slot Verbindung)
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FileUtils, &FileUtils::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_UsbHidLoader, &UsbHidLoader::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_InactivityWatcher, &InactivityWatcher::OnProcessMessage, Qt::DirectConnection);

			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_FileUtils, &FileUtils::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_UsbHidLoader, &UsbHidLoader::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_InactivityWatcher, &InactivityWatcher::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			m_logger->flush();
		}


		ProcessManager::~ProcessManager()
		{
		}
	}
}
