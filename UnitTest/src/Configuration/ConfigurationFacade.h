#pragma once
#include "qobject.h"
#include "ConfigurationGlobal.h"
#include "spdlog\spdlog.h"

namespace RW{
	namespace CORE{
		class ConfigurationFacade :
			public QObject
		{
			Q_OBJECT
		private:
			/*
			@brief Instanz des Loggers
			*/
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			ConfigurationFacade(QObject *Parent = nullptr);
			~ConfigurationFacade();
		public slots: 
		void OnReadOrUpdateAppSettings(QMap<ConfigurationKey, QVariant> *ApplicationSettings);
		void OnReadOrUpdateUserSettings(QMap<ConfigurationKey, QVariant> *UserSettings);
		};
	}
}
