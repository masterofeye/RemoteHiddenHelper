#include "ProductFactory.h"

#include "ProductMapperSQL.h"
#include "ProductMapperXML.h"

namespace RW{
	namespace SQL{
		ProductFactory::ProductFactory(QObject *Parent) : DataFactory(Parent)
		{
		}


		ProductFactory::~ProductFactory()
		{
		}

		DataMapper* ProductFactory::GetMapper(DataMapper::SourceType Source)
		{
			switch (Source)
			{
			case RW::SQL::DataMapper::SourceType::SQL:
				return new ProductMapperSQL();
				break;
			case RW::SQL::DataMapper::SourceType::XML:
				return new ProductMapperXML();
				break;
			case RW::SQL::DataMapper::SourceType::MOCK:
				return nullptr;
				break;
			default:
				return nullptr;
				break;
			}
		}
	}
}