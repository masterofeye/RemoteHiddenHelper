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
		class InactivityWatcher;
        class MessageWrapper;
        class ExitHandler;
		

		class ProcessManager :
			public QObject
		{
			Q_OBJECT
		private:
            std::shared_ptr<spdlog::logger> m_Logger;
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
            ExitHandler* m_ExitHandler;
		public:
			ProcessManager(QObject* Parent = nullptr);
			~ProcessManager();
        public slots:
            /**************************************************************************************************************//**
            @autor Ivo Kunadt
            @brief Message Verarbeitungsroutine, Alle Nachrichten die vom CommunikationsManager empfangen werden, weden zunächst
            an diesen Slot geleitet und werden im Anschluss gefiltert. Nachrichten die nicht dem Filter entsprechen werden
            verworfen.
            @param[in] Type Basistype der Nachricht
            @param[in] Func Arbeitsschritt der durchgeführt werden soll
            @param[in] Report Userdaten, die eine oder mehrere Informationen enthalten können. Die Daten werden dabei mit einem
            QDataStream in die Nachricht geschrieben.
            @return void
            ********************************************************************************************************************/
            virtual void OnProcessMessage(COM::Message Msg);
        signals:		
            void NewMessage(COM::Message Msg);
            void ResetPermanentCheckBox();
            void CheckPermanentCheckBox(bool Checked);

		};
	}
}