#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class RemoteWorkstationMapperSQL : public DataMapper
		{
			Q_OBJECT
		private: 
			const QString TableName = "remoteWorkstation";
		public:
			RemoteWorkstationMapperSQL(DataMapper *Parent = nullptr);
			~RemoteWorkstationMapperSQL();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};

	}
}