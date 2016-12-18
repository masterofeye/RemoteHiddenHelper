#include "ElementType.h"

namespace RW{
	namespace SQL{

		ElementType::ElementType(Entity *Parent) : Entity(Parent),
			m_Type(TypeOFElement::INVALID)
		{
		}


		ElementType::~ElementType()
		{
		}

		ElementType& ElementType::operator=(const ElementType &obj)
		{
			if (this != &obj)
			{
				m_Type = obj.m_Type;
			}
			return *this;
		}
	}
}