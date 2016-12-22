#include "ElementType.h"
#include "ElementType_p.h"
#include "SQLGlobal.h"

namespace RW{
	namespace SQL{

		ElementTypePrivate::ElementTypePrivate(ElementType *Parent) :
			QObject(Parent),
			m_Type(RW::TypeOfElement::INVALID),
			q_ptr(Parent)
		{
		}

		ElementTypePrivate::~ElementTypePrivate()
		{}

		ElementType::ElementType(Entity *Parent) : Entity(Parent),
			d_ptr(new ElementTypePrivate(this))
		{
		}

		ElementType::~ElementType()
		{
			delete d_ptr;
		}

		RW::TypeOfElement ElementType::Type()
		{
			Q_D(ElementType);
			return d_ptr->m_Type;
		}

		void ElementType::SetType(RW::TypeOfElement Type)
		{ 
			Q_D(ElementType);
			d_ptr->m_Type = Type;
			emit d_ptr->TypeChanged();
		}
	}
}