#include "Instruction.h"

namespace RW{
	namespace SQL{

		Instruction::Instruction(Entity *Parent) : Entity(Parent),
			m_Step("")
		{
		}


		Instruction::~Instruction()
		{
		}
	}
}
