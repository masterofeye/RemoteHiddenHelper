#include "ReceptFactory.h"
#include "ReceptMapperSQL.h"
#include "ReceptMapperXML.h"

namespace RW{
	namespace SQL{
		ReceptFactory::ReceptFactory(QObject *Parent) : DataFactory(Parent)
		{
		}


		ReceptFactory::~ReceptFactory()
		{
		}

		DataMapper* ReceptFactory::GetMapper(DataMapper::SourceType Source)
		{
			switch (Source)
			{
			case RW::SQL::DataMapper::SourceType::SQL:
				return new ReceptMapperSQL();
				break;
			case RW::SQL::DataMapper::SourceType::XML:
				return new ReceptMapperXML();
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
