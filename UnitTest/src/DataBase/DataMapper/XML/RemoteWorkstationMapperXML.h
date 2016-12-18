#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class RemoteWorkstationMapperXML :
			public DataMapper
		{
			Q_OBJECT
		public:
			RemoteWorkstationMapperXML(DataMapper *Parent = nullptr);
			~RemoteWorkstationMapperXML();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};
	}
}