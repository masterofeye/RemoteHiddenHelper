#pragma once
#include "qobject.h"

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
		void OnReadOrUpdateAppSettings(QMap<QString, QVariant> *ApplicationSettings);
		void OnReadOrUpdateUserSettings(QMap<QString, QVariant> *UserSettings);
		};
	}
}
