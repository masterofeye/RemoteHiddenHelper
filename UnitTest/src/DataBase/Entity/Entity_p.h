#pragma once
#include <qobject.h>

namespace RW{
	namespace SQL{

		class Entity;
		class EntityPrivate : public QObject
		{
			Q_OBJECT
				Q_DISABLE_COPY(EntityPrivate)
				Q_DECLARE_PUBLIC(Entity)
		private:
			Entity * const q_ptr;
		public:
			quint64 m_ID;
		public:
			EntityPrivate(Entity *Parent);
			~EntityPrivate();
		};
	}
}