#include "ReceptMapperXML.h"
#include "Recept.h"

namespace RW{
	namespace SQL{

		ReceptMapperXML::ReceptMapperXML(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		ReceptMapperXML::~ReceptMapperXML()
		{
		}


		bool ReceptMapperXML::Insert(const Entity &Data)
		{
			return false;
		}

		bool ReceptMapperXML::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& ReceptMapperXML::FindByID(const quint64 id)
		{
			Recept e;

			return std::move(e);
		}

		QList<Entity>&& ReceptMapperXML::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}