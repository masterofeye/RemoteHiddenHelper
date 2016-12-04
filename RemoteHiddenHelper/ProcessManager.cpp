#include "ProcessManager.h"

#include "CommunicationManager.h"
#include "CanEasyWrapper.h"
#include "FHostSpWrapper.h"
#include "MKSWrapper.h"
#include "PortalInfo.h"
#include "ErrorHandler.h"

namespace RW{
	namespace CORE{

		ProcessManager::ProcessManager(QObject* Parent) : QObject(Parent),
			m_CanEasy(new CanEasyWrapper(this)),
			m_FHostSP(new FHostSpWrapper(this)),
			m_PortalInfo(new PortalInfo(this)),
			m_MKS(new MKSWrapper(this)),
            m_ErrorHandler(new ErrorHandler(this))
            
		{
            m_CommManager = new CommunicationManager(m_ErrorHandler, this);

			//Zuert wird der CommunikationManager bedient .... 
			connect(m_CommManager, &CommunicationManager::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage,Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_CommManager, &CommunicationManager::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);

			//...danach erh�lt der Errorhandler die Informationen (Reihenfolge der Signal/Slot Verbindung)
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_CanEasy, &CanEasyWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_FHostSP, &FHostSpWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_MKS, &MKSWrapper::OnProcessMessage, Qt::DirectConnection);
			connect(m_ErrorHandler, &ErrorHandler::NewMessage, m_PortalInfo, &PortalInfo::OnProcessMessage, Qt::DirectConnection);

			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_CommManager, &CommunicationManager::OnProcessMessageAnswer, Qt::DirectConnection);

			connect(m_CanEasy, &CanEasyWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_FHostSP, &FHostSpWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_MKS, &MKSWrapper::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
			connect(m_PortalInfo, &PortalInfo::NewMessage, m_ErrorHandler, &ErrorHandler::OnProcessMessageAnswer, Qt::DirectConnection);
		}


		ProcessManager::~ProcessManager()
		{
		}
	}
}