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
        class FileUtils;
        class UsbHidLoader;
		class ShutdownHandler;
		class InactivityWatcher;
		

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
            FileUtils* m_FileUtils;
            UsbHidLoader* m_UsbHidLoader;
			InactivityWatcher* m_InactivityWatcher;
			ShutdownHandler* m_ShutdownHandler;
		public:
			ProcessManager(QObject* Parent = nullptr);
			~ProcessManager();
		};
	}
}