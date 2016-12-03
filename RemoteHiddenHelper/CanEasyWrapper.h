#pragma once
#include "BasicWrapper.h"
#include "atlbase.h"

#import "C:\Program Files (x86)\CanEasy\CanEasy.exe" no_namespace raw_native_types raw_interfaces_only
#import "C:\Program Files (x86)\CanEasy\COMSvr.dll" no_namespace raw_native_types raw_interfaces_only

class QFile;

namespace RW{
	namespace CORE{

		class CanEasyWrapper :
			public BasicWrapper
		{
			Q_OBJECT
		private: 
			CComPtr<ICanEasyProcess> m_Process;
			CComPtr<ICanEasyApplication> m_App;
            bool m_IsRunning;
		public:
			CanEasyWrapper(QObject* Parent = nullptr);
			~CanEasyWrapper();
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
			virtual void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);
		private:
			void StartCanEasy(const QFile &CanEasyInstallionDir);
			void StartSimulation();
			void StopSimulation();
			void LoadWorkspace(const QFile &Workspace);
			void StopCanEasy();
            void CloseExplicit();


		};
	}
}
