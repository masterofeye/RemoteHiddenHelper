#include "ReceptMapperSQL.h"
#include "Recept.h"

namespace RW{
	namespace SQL{
		ReceptMapperSQL::ReceptMapperSQL(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		ReceptMapperSQL::~ReceptMapperSQL()
		{
		}

		bool ReceptMapperSQL::Insert(const Entity &Data)
		{
			return false;
		}

		bool ReceptMapperSQL::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& ReceptMapperSQL::FindByID(const quint64 id)
		{
			Recept e;

			return std::move(e);
		}

		QList<Entity>&& ReceptMapperSQL::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}