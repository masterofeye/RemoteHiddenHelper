#pragma once
#include "qobject.h"
#include "ConfigurationGlobal.h"

namespace RW{
	namespace CORE{
		class ConfigurationFacade :
			public QObject
		{
			Q_OBJECT
		public:
			ConfigurationFacade(QObject *Parent = nullptr);
			~ConfigurationFacade();
		public slots: 
		void OnReadOrUpdateAppSettings(QMap<ConfigurationKey, QVariant> *ApplicationSettings);
		void OnReadOrUpdateUserSettings(QMap<ConfigurationKey, QVariant> *UserSettings);
		};
	}
}
