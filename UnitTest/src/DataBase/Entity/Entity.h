#pragma once

#include "qobject.h"
namespace RW{
	namespace SQL{
		class Entity :
			public QObject
		{
			Q_OBJECT
			Q_PROPERTY(quint64 ID MEMBER m_ID READ ID WRITE SetID NOTIFY IDChanged)
		private:
			quint64 m_ID;
		public:
			Entity(QObject *Parent = nullptr);
			~Entity();
			Entity(const Entity &obj);
			Entity& Entity::operator=(const Entity &obj);

			Entity(Entity &&rvalue);
			Entity& Entity::operator=(Entity&& other);

			quint64 ID() const { return m_ID; };
			void SetID(quint64 ID){ m_ID = ID; emit IDChanged(m_ID); };
		signals:
			void IDChanged(quint64);

		};
	}
}
