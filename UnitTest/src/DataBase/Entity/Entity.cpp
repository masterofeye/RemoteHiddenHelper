#include "Entity.h"
#include "Entity_p.h"
#include "qdebug.h"

namespace RW{
	namespace SQL{


		EntityPrivate::EntityPrivate(Entity *Parent) :
			QObject(Parent),
			m_ID(0),
			q_ptr(Parent)
		{
			qDebug() << "CTor EntityPrivate";
		}

		EntityPrivate::~EntityPrivate()
		{
			qDebug() << "~CTor EntityPrivate";
		}

		Entity::Entity(QObject *Parent) : QObject(Parent),
			d_ptr(new EntityPrivate(this))
		{
			qDebug() << "CTor Entity";
		}


		Entity::~Entity()
		{
			qDebug() << "~CTor Entity";
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

		Entity::Entity(Entity &&other) : d_ptr(other.d_ptr)
		{
			other.d_ptr = nullptr;
		}

		Entity& Entity::operator=(Entity&& other)
		{
			std::swap(d_ptr, other.d_ptr);
			delete other.d_ptr;
			other.d_ptr = nullptr;
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