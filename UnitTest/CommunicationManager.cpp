#include "CommunicationManager.h"

namespace RW{
	namespace CORE{

		CommunicationManager::CommunicationManager(QObject *Parent) :QObject(Parent)
		{
		}


		CommunicationManager::~CommunicationManager()
		{
		}

		void CommunicationManager::OnProcessMessage(QVariant Data)
		{
		}
	}
}