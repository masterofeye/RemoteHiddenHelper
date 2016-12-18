#include "ConfigurationFacade.h"

namespace RW{
	namespace CORE{
		ConfigurationFacade::ConfigurationFacade(QObject *Parent) : QObject(Parent)
		{
		}


		ConfigurationFacade::~ConfigurationFacade()
		{
		}

		void ConfigurationFacade::OnReadOrUpdateAppSettings(QMap<QString, QVariant> *ApplicationSettings)
		{

		}

		void ConfigurationFacade::OnReadOrUpdateUserSettings(QMap<QString, QVariant> *UserSettings)
		{


		}
	}
}