#include "Entity.h"
#include "Entity_p.h"

namespace RW{
	namespace SQL{


		EntityPrivate::EntityPrivate(Entity *Parent) :
			QObject(Parent),
			m_ID(0),
			q_ptr(Parent)
		{
		}

		EntityPrivate::~EntityPrivate()
		{}

		Entity::Entity(QObject *Parent) : QObject(Parent),
			d_ptr(new EntityPrivate(this))
		{
		}


		Entity::~Entity()
		{
			delete d_ptr;
		}

		Entity::Entity(const Entity &obj) : d_ptr(new EntityPrivate(this))
		{
			Q_D(Entity);
			if (this != &obj)
			{
				d->m_ID = obj.ID();
			}
		}
		
		Entity& Entity::operator=(const Entity &obj)
		{
			Q_D(Entity);
			if (this != &obj)
			{
				d->m_ID = obj.ID();
			}
			return *this;
		}

		Entity::Entity(Entity &&rvalue)
		{
			Q_D(Entity);
			SetID(0);
			d->m_ID = rvalue.ID();
			rvalue.SetID(0);
		}

		Entity& Entity::operator=(Entity&& other)
		{
			Q_D(Entity);
			if (this != &other)
			{
				d->m_ID = 0;

				d->m_ID = other.ID();

				other.SetID(0);
			}
			return *this;
		}

		quint64 Entity::ID() const {
			Q_D(const Entity);
			return d->m_ID; 
		};
		void Entity::SetID(quint64 ID)
		{ 
			Q_D(Entity);
			d->m_ID = ID; 
			emit IDChanged(d->m_ID); };
	}
}