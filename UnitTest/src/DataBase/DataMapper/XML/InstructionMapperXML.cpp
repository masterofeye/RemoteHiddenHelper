#include "InstructionMapperXML.h"
#include "Instruction.h"

namespace RW{
	namespace SQL{

		InstructionMapperXML::InstructionMapperXML(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		InstructionMapperXML::~InstructionMapperXML()
		{
		}


		bool InstructionMapperXML::Insert(const Entity &Data)
		{
			return false;
		}

		bool InstructionMapperXML::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& InstructionMapperXML::FindByID(const quint64 id)
		{
			Instruction e;

			return std::move(e);
		}

		QList<Entity>&& InstructionMapperXML::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}