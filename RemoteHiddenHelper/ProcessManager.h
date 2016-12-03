#pragma once
#include "qobject.h"

namespace RW{
	namespace CORE{
		class CommunicationManager;
		class CanEasyWrapper;
		class MKSWrapper;
		class FHostSpWrapper;
		class PortalInfo;
        class ErrorHandler;
		

		class ProcessManager :
			public QObject
		{
			Q_OBJECT
		private:
			CommunicationManager* m_CommManager;
			CanEasyWrapper* m_CanEasy;
			MKSWrapper* m_MKS;
			FHostSpWrapper* m_FHostSP;
			PortalInfo* m_PortalInfo;
            ErrorHandler* m_ErrorHandler;
		public:
			ProcessManager(QObject* Parent = nullptr);
			~ProcessManager();
		};
	}
}