#pragma once

#include "qobject.h"

namespace RW{
	namespace SQL{
		class EntityPrivate;
		class Entity :
			public QObject
		{
			Q_OBJECT
			Q_PROPERTY(quint64 ID READ ID WRITE SetID NOTIFY IDChanged)
		private:
			EntityPrivate* d_ptr;
			Q_DECLARE_PRIVATE(Entity);
		public:
			Entity(QObject *Parent = nullptr);
			~Entity();
			Entity(const Entity &obj);
			Entity& Entity::operator=(const Entity &obj);

			Entity(Entity &&rvalue);
			Entity& Entity::operator=(Entity&& other);

			quint64 ID() const;
			void SetID(quint64 ID);
		signals:
			void IDChanged(quint64);

		};
	}
}
