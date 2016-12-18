#include "RemoteWorkstationMapperSQL.h"
#include "RemoteWorkstation.h"

#include <qsqlquery.h>

namespace RW{
	namespace SQL{
		RemoteWorkstationMapperSQL::RemoteWorkstationMapperSQL(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		RemoteWorkstationMapperSQL::~RemoteWorkstationMapperSQL()
		{
		}

		bool RemoteWorkstationMapperSQL::Insert(const Entity &Data)
		{
			const RemoteWorkstation *data = dynamic_cast<const RemoteWorkstation* >(&Data);
			if (data == nullptr)
			{
				return false;
			}
			QSqlQuery query;
			query.exec("INSERT INTO " + TableName + " (elementConfigurationID, userID, hostname, mac, ip) VALUES (:elementConfigurationID, :userID, :hostname; mac, ip)");
			//query.bindValue(":elementConfigurationID", )

			return false;
		}

		bool RemoteWorkstationMapperSQL::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& RemoteWorkstationMapperSQL::FindByID(quint64 id)
		{
			RemoteWorkstation e;

			return std::move(e);
		}

		QList<Entity>&& RemoteWorkstationMapperSQL::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}