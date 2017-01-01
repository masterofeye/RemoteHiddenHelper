#include "ConfigurationFacade.h"
#include "Repository.h"

#include "AllEntities.h"

Q_DECLARE_METATYPE(RW::SQL::RemoteWorkstation);
Q_DECLARE_METATYPE(QList<RW::SQL::RemoteWorkstation>);
namespace RW{
	namespace CORE{
		ConfigurationFacade::ConfigurationFacade(QObject *Parent) : QObject(Parent)
		{
		}


		ConfigurationFacade::~ConfigurationFacade()
		{
		}

		void ConfigurationFacade::OnReadOrUpdateAppSettings(QMap<ConfigurationKey, QVariant> *ApplicationSettings)
		{
			SQL::Repository repository(SourceType::SQL);
			qRegisterMetaType<QList<RW::SQL::RemoteWorkstation>>("QList<RW::SQL::RemoteWorkstation>");
			//qRegisterMetaTypeStreamOperators<QList<RW::SQL::RemoteWorkstation>>("QList<RW::SQL::RemoteWorkstation>");

			QList<RW::SQL::RemoteWorkstation> remoteWorkstationList;
			repository.GetAllRemoteWorkstation(remoteWorkstationList);

			ApplicationSettings->insert(ConfigurationKey::RemoteWorkstations, QVariant::fromValue(remoteWorkstationList));


			
		}

		void ConfigurationFacade::OnReadOrUpdateUserSettings(QMap<ConfigurationKey, QVariant> *UserSettings)
		{
			SQL::Repository repository(SourceType::SQL);
			QString Username;
			SQL::User user;
			repository.GetUserByName(Username, user);

		}
	}
}