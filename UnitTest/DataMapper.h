#pragma once
#include "qobject.h"
#include "Entity.h"

namespace RW{
	namespace SQL{
		class Entity;

		class DataMapper :
			public QObject
		{
			Q_OBJECT
		public:
			enum class SourceType
			{
				SQL,
				XML,
				MOCK
			};
			Q_ENUM(SourceType);

			DataMapper(QObject* Parent = nullptr);
			~DataMapper();
		public:
			virtual bool Insert(const Entity &Data) = 0;
			virtual bool Update(const Entity &Data) = 0;
			virtual Entity&& FindByID(const quint64 id) = 0;
			virtual QList<Entity>&& FindAll() = 0;
		};
	}
}