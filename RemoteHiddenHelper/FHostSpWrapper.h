#pragma once
#include "BasicWrapper.h"
#include <qfile.h>

#include "atlbase.h"
#import "C:\Program Files (x86)\FHostSP\FHostSp.exe" no_namespace raw_native_types raw_interfaces_only

namespace RW{
	namespace CORE{

		const QString ClassNameFHostSP = "Afx:00400000:8:00010005:00000000:CEF10A4F";
		const QString WindowNameFHostSP = "";

		class FHostSpWrapper :
			public BasicWrapper
		{
			Q_OBJECT
		private:
			CComPtr<IFHostSP_RemoteInterface> m_Process;
			std::string m_WorkspacePath;
		public slots:
			/***************************************************************************************************************//**
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
			void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);
		public:
			FHostSpWrapper(QObject* Parent = nullptr);
			~FHostSpWrapper();

			void StartFHostSP();
			void CloseSequence();
			void GetProgress();
			void CloseApplication();
			void GetState();
			void AbortSequence();
            void LoadSequence(const QFile &Flashfile);
			void StartSequence();
		private: 
			QString FHostSpWrapper::ReadStatusText();
		};

	}
}