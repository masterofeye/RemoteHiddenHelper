#include "ProductMapperSQL.h"
#include "Product.h"

namespace RW{
	namespace SQL{
		ProductMapperSQL::ProductMapperSQL(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		ProductMapperSQL::~ProductMapperSQL()
		{
		}

		bool ProductMapperSQL::Insert(const Entity &Data)
		{
			return false;
		}

		bool ProductMapperSQL::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& ProductMapperSQL::FindByID(const quint64 id)
		{
			Product e;

			return std::move(e);
		}

		QList<Entity>&& ProductMapperSQL::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}