#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class ReceptMapperSQL : public DataMapper
		{
			Q_OBJECT
		public:
			ReceptMapperSQL(DataMapper *Parent = nullptr);
			~ReceptMapperSQL();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};

	}
}