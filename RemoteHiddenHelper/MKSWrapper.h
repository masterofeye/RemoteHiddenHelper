#pragma once
#include "BasicWrapper.h"

class QFile;


namespace RW{
	namespace CORE{

		class MKSWrapper : public BasicWrapper
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
			explicit MKSWrapper(QObject* Parent = nullptr);
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
			virtual void OnProcessMessage(COM::Message Msg);
		private: 
			/*****************************************************************************************************************//*
			@autor Ivo Kunadt
			@brief Löscht die Sandbox aus dem MKS Client. Die Dateien bleiben weiterhin bestehen.
			@return void
			********************************************************************************************************************/
			void StartMKS(QString MKSLocation, QString Username, QString Password, QString Server = "ims-id", quint16 Port = 7001, QString Proxy = "MKS-PROXY", quint16 ProxyPort = 7023);

			/*****************************************************************************************************************//*
			@autor Ivo Kunadt
			@brief Erzeugt eine Sandbox im MKS Client und lädt alle Dateien in der Sandbox am Zielort ab.
			@param[in] MksUrl Pfad zur Datei auf dem MKS Server.
			@param[in] Destination Ziel an dem die Datei auf den lokalen Rechner abgelegt werden soll.
			@return void
			********************************************************************************************************************/
            void CreateSandBox(QString MksUrl, QString Destination);

			/*****************************************************************************************************************//*
			@autor Ivo Kunadt
			@brief Löscht die Sandbox aus dem MKS Client. Die Dateien bleiben weiterhin bestehen.
			@return void
			********************************************************************************************************************/
			void DropSandBox(); 
			
			/*****************************************************************************************************************//*
			@autor Ivo Kunadt
			@brief Schließt den MKS Client und baut somit die Verbindung zum MKS-Server ab.
			@return void
			********************************************************************************************************************/
			void MKSWrapper::CloseMKS();

			void PrepareMKSLoginForm();

		};

	}
}
