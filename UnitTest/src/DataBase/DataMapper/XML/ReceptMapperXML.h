#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class ReceptMapperXML :
			public DataMapper
		{
			Q_OBJECT
		public:
			ReceptMapperXML(DataMapper *Parent = nullptr);
			~ReceptMapperXML();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};
	}
}