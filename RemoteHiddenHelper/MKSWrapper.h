#pragma once
#include "BasicWrapper.h"

class QFile;


namespace RW{
	namespace CORE{

		class MKSWrapper :
			public BasicWrapper
		{
			Q_OBJECT
		private:
			QString m_MKSLocation;
			QString m_Server;
			QString m_ProxyServer;
			quint16 m_ProxyPort;
			quint16 m_Port;
			QString m_Destination;
		public:
			MKSWrapper(QObject* Parent = nullptr);
			~MKSWrapper();
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
			void StartMKS(QString MKSLocation, QString Username, QString Password, QString Server = "ims-id", quint16 Port = 7001, QString Proxy = "MKS-PROXY", quint16 ProxyPort = 7023);
			void CreateSandBox(QString MksUrl, QString Destination);
			//void DownloadFlashFiles(QString MksUrl, QString Destination);
			void DropSandBox();

		};

	}
}
