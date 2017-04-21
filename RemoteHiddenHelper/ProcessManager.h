#pragma once
#include "qobject.h"
#include "RemoteUtil\RemoteCommunicationLibrary\Include\RemoteCommunicationLibrary.h"


namespace RW{
	namespace CORE{
		class CanEasyWrapper;
		class MKSWrapper;
		class FHostSpWrapper;
		class PortalInfo;
        class ErrorHandler;
        class FileUtils;
        class UsbHidLoader;
		class ShutdownHandler;
		class InactivityWatcher;
        class MessageWrapper;
		

		class ProcessManager :
			public QObject
		{
			Q_OBJECT
		private:
			std::shared_ptr<spdlog::logger> m_logger;
			CanEasyWrapper* m_CanEasy;
			MKSWrapper* m_MKS;
			FHostSpWrapper* m_FHostSP;
			PortalInfo* m_PortalInfo;
            ErrorHandler* m_ErrorHandler;
            FileUtils* m_FileUtils;
            UsbHidLoader* m_UsbHidLoader;
			InactivityWatcher* m_InactivityWatcher;
			COM::CommunicatonServer* m_CommunicationServer;
            MessageWrapper *m_MessageWrapper;
		public:
			ProcessManager(QObject* Parent = nullptr);
			~ProcessManager();
		};
	}
}