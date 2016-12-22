#include "Recept.h"
#include "Recept_p.h"

namespace RW{
	namespace SQL{

		ReceptPrivate::ReceptPrivate(Recept *Parent) : 
			QObject(Parent),
			q_ptr(Parent),
			m_OrderNumber(0),
			m_InstructionID(0),
			m_ReceptName("")
		{
		
		}

		ReceptPrivate::~ReceptPrivate()
		{}

		Recept::Recept(Entity *Parent) : Entity(Parent),
			d_ptr(new ReceptPrivate(this))
		{
		}


		Recept::~Recept()
		{
			delete d_ptr;
		}

		Instruction& Recept::Instruction()
		{ 
			Q_D(Recept);
			return d->m_InstructionID;
		}
		void Recept::SetInstruction(RW::SQL::Instruction& ReceptID)
		{
			Q_D(Recept); 
			d->m_InstructionID = ReceptID;
			emit InstructionChanged();
		}

		quint16 Recept::OrderNumber()
		{ 
			Q_D(Recept);
			return d->m_OrderNumber; 
		}
		void Recept::SetOrderNumber(quint16 Order)
		{ 
			Q_D(Recept);
			d->m_OrderNumber = Order; 
			emit OrderNumberChanged(); 
		}

		QString Recept::ReceptName()
		{ 
			Q_D(Recept);
			return d->m_ReceptName; 
		}
		void Recept::SetReceptName(QString Order)
		{ 
			Q_D(Recept);
			d->m_ReceptName = Order; 
			emit ReceptNameChanged(); 
		}
	}
}