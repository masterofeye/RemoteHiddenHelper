#include "InstructionFactory.h"

#include "InstructionMapperSQL.h"
#include "InstructionMapperXML.h"

namespace RW{
	namespace SQL{
		InstructionFactory::InstructionFactory(QObject *Parent) : DataFactory(Parent)
		{
		}


		InstructionFactory::~InstructionFactory()
		{
		}

		DataMapper* InstructionFactory::GetMapper(DataMapper::SourceType Source)
		{
			switch (Source)
			{
			case RW::SQL::DataMapper::SourceType::SQL:
				return new InstructionMapperSQL();
				break;
			case RW::SQL::DataMapper::SourceType::XML:
				return new InstructionMapperXML();
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