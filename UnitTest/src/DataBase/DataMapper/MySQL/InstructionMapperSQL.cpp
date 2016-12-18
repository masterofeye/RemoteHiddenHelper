#include "InstructionMapperSQL.h"
#include "Instruction.h"

namespace RW{
	namespace SQL{
		InstructionMapperSQL::InstructionMapperSQL(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		InstructionMapperSQL::~InstructionMapperSQL()
		{
		}

		bool InstructionMapperSQL::Insert(const Entity &Data)
		{
			return false;
		}

		bool InstructionMapperSQL::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& InstructionMapperSQL::FindByID(const quint64 id)
		{
			Instruction e;

			return std::move(e);
		}

		QList<Entity>&& InstructionMapperSQL::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}