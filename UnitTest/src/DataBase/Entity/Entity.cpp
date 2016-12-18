#include "Entity.h"

namespace RW{
	namespace SQL{
		Entity::Entity(QObject *Parent) : QObject(Parent)
		{
		}


		Entity::~Entity()
		{
		}

		Entity::Entity(const Entity &obj)
		{
			if (this != &obj)
			{
				m_ID = obj.m_ID;
			}
		}
		
		Entity& Entity::operator=(const Entity &obj)
		{
			if (this != &obj)
			{
				m_ID = obj.m_ID;
			}
			return *this;
		}

		Entity::Entity(Entity &&rvalue) : m_ID(0)
		{
			m_ID = rvalue.m_ID;
			rvalue.m_ID = 0;
		}

		Entity& Entity::operator=(Entity&& other)
		{
			if (this != &other)
			{
				m_ID = 0;

				m_ID = other.m_ID;

				other.m_ID = 0;
			}
			return *this;
		}
	}
}