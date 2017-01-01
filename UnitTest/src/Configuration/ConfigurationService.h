#pragma once
#include "qobject.h"
#include <qvariant.h>
#include "ConfigurationGlobal.h"


namespace RW{
	namespace CORE{
		class ConfigurationFacade;

		class ConfigurationService :
			public QObject
		{
			Q_OBJECT
		private:
			QMap<ConfigurationKey, QVariant> *m_UserSettings;
			QMap<ConfigurationKey, QVariant> *m_ApplicationSettings;
			
			/**
			@brief Enthält eine Liste an Clienten und deren Konfigurationselementen. Es ist möglich das ein Client mehrere Konfigurationselemente abboniert hat.
			*/
			QMultiMap<QObject*, QString> *m_NotificationList;

			ConfigurationFacade *m_ServiceLayer;
		public:
			ConfigurationService(QObject *Parent = nullptr);
			~ConfigurationService();

			/*
			@brief Bietet einem Clienten die Möglichkeit sich für das Empfangen von Konfigurationsinformationen zu registrieren.
			@param Client
			@param Key Das Konfigurationselement für das sich der Client interesiert.
			*/
			void Register(QObject *Receiver, QString Key);
			void UnregisterAll();
		public slots:
			void OnProcessMessage(QVariant Data);

			/**
			@brief Empfängt die Daten die ein Client in der Konfiguration ablegen will
			*/
			void OnChangeConfiguration(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data);

			/**
			@brief Dieser Slot bietet die Möglichkeit ein erneutes einlesen der Konfiguration zu triggern. 
			*/
			void ReadUsersettings(){ emit ReadOrUpdateUserSettings(m_UserSettings); }
			void ReadApplicationSettings(){ emit ReadOrUpdateAppSettings(m_ApplicationSettings); }
		signals: 
			/*
			@brief Diese Signal wird jedes mal dann ausgelöst wenn sich ein Setting geändert hat
			@param [in] Type Der Typ gibt an, ob die Settings initial geladen wurden oder ob es sich um ein Update handelt
			@param [in] Receiver 
			@param [in] Data Settings die sich geändert haben
			*/
			void ConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data);

			void ReadOrUpdateAppSettings(QMap<ConfigurationKey, QVariant> *ApplicationSettings);
			void ReadOrUpdateUserSettings(QMap<ConfigurationKey, QVariant> *UserSettings);
		};

	}
}