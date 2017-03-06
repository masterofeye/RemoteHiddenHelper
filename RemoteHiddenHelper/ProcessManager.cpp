#include "ProcessManager.h"

#include "CommunicationManager.h"
#include "CanEasyWrapper.h"
#include "FHostSpWrapper.h"
#include "MKSWrapper.h"
#include "PortalInfo.h"
#include "ErrorHandler.h"
#include "FileUtils.h"
#include "UsbHidLoader.h"
#include "Inactivitywatcher.hpp"
#include "ShutdownHandler.hpp"

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
			m_InactivityWatcher(new InactivityWatcher(this)),
			m_ShutdownHandler(new ShutdownHandler(this))
            
		{
            m_CommManager = new CommunicationManager(m_ErrorHandler, this);

			//Zuert wird der CommunikationManager bedient .... 
			connect(m_CommManager, &CommunicationManager::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage,Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);
            connect(m_CommManager, &CommunicationManager::NewMessage, m_FileUtils, &FileUtils::OnProcessMessage, Qt::DirectConnection);
            connect(m_CommManager, &CommunicationManager::NewMessage, m_UsbHidLoader, &UsbHidLoader::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_UsbHidLoader, &UsbHidLoader::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_InactivityWatcher, &InactivityWatcher::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_ShutdownHandler, &ShutdownHandler::OnProcessMessage, Qt::DirectConnection);

			//...danach erh�lt der Errorhandler die Informationen (Reihenfolge der Signal/Slot Verbindung)
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FileUtils, &FileUtils::OnProcessMessage, Qt::DirectConnection);
            connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_UsbHidLoader, &UsbHidLoader::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_InactivityWatcher, &InactivityWatcher::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_ShutdownHandler, &ShutdownHandler::OnProcessMessage, Qt::DirectConnection);


			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_FileUtils, &FileUtils::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_UsbHidLoader, &UsbHidLoader::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_InactivityWatcher, &InactivityWatcher::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_ShutdownHandler, &ShutdownHandler::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);

			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_FileUtils, &FileUtils::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
            connect(m_UsbHidLoader, &UsbHidLoader::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_InactivityWatcher, &InactivityWatcher::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_ShutdownHandler, &ShutdownHandler::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
		}


		ProcessManager::~ProcessManager()
		{
		}
	}
}
