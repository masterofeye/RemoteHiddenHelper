#include "ElementType.h"
#include "ElementType_p.h"
#include "SQLGlobal.h"
#include "qdebug.h"

namespace RW{
	namespace SQL{

		ElementTypePrivate::ElementTypePrivate(ElementType *Parent) :
			//QObject(Parent),
			m_Type(RW::TypeOfElement::INVALID),
			q_ptr(Parent)
		{
			qDebug() << "ctor ElementTypePrivate";
		}

		ElementTypePrivate::~ElementTypePrivate()
		{
			qDebug() << "~ctor ElementTypePrivate";
		}

		ElementType::ElementType(Entity *Parent) : Entity(Parent),
			d_ptr(new ElementTypePrivate(this))
		{
			qDebug() << "ctor ElementType";
		}

		ElementType::~ElementType()
		{
			qDebug() << "~ctor ElementType";
		}

		ElementType::ElementType(const ElementType& other)
		{


		}

		ElementType& ElementType::operator=(ElementType& other)
		{
			return *this;
		}

		ElementType::ElementType(ElementType&& other)
		{
		
		}

		ElementType& ElementType::operator=(ElementType&& other)
		{
			this->SetType(other.Type());
			other.SetType(RW::TypeOfElement::INVALID);
			return *this;
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