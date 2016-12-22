#include "Instruction.h"
#include "Instruction_p.h"

namespace RW{
	namespace SQL{

		InstructionPrivate::InstructionPrivate(Instruction* QPointer):
			q_ptr(QPointer),
			m_Step("")
		{
		
		}
		
		InstructionPrivate::~InstructionPrivate(){}


		Instruction::Instruction(Entity *Parent) : Entity(Parent),
			d_ptr(new InstructionPrivate(this))
		{
		}


		Instruction::~Instruction()
		{
			delete d_ptr;
		}

		QString Instruction::Step()
		{
			Q_D(Instruction);
			return d->m_Step;
		}

		void Instruction::SetStep(QString Step)
		{ 
			Q_D(Instruction);
			d->m_Step = Step; 
		}
	}
}
