#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class ProductMapperSQL : public DataMapper
		{
			Q_OBJECT
		public:
			ProductMapperSQL(DataMapper *Parent = nullptr);
			~ProductMapperSQL();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};

	}
}