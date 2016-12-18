#include "ElementConfiguration.h"

#include "ElementType.h"
namespace RW{
	namespace SQL{

		ElementConfiguration::ElementConfiguration(Entity *Parent) : Entity(Parent),
			m_DisplayName(""),
			m_Function(""),
			m_Group(""),
			m_Type(new ElementType()),
			m_Name("")
		{
		}


		ElementConfiguration::~ElementConfiguration()
		{
			delete m_Type;
		}

		ElementConfiguration& ElementConfiguration::operator=(const ElementConfiguration &obj)
		{
			if (this != &obj)
			{
				m_DisplayName = obj.m_DisplayName;
				m_Function = obj.m_Function;
				m_Group = obj.m_Group;
				m_Name = obj.m_Name;
				m_Type = obj.m_Type;
			}
			return *this;
		}

		void ElementConfiguration::SetType(ElementType &Type){ *m_Type = Type; emit TypeChanged(); }
	}
}
