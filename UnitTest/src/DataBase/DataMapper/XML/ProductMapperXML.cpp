#include "ProductMapperXML.h"
#include "Product.h"

namespace RW{
	namespace SQL{

		ProductMapperXML::ProductMapperXML(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		ProductMapperXML::~ProductMapperXML()
		{
		}


		bool ProductMapperXML::Insert(const Entity &Data)
		{
			return false;
		}

		bool ProductMapperXML::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& ProductMapperXML::FindByID(const quint64 id)
		{
			Product e;

			return std::move(e);
		}

		QList<Entity>&& ProductMapperXML::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}