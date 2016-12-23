#pragma once
#include "qobject.h"
#include "Entity.h"

namespace RW{
	namespace SQL{
		class Entity;
		template <class T>
		class DataMapper
		{
		public:

			virtual bool Insert(const T &Data) = 0;
			virtual bool Update(const T &Data) = 0;
			virtual T FindByID(const quint64 id,bool Flag) = 0;
			virtual QList<T> FindAll() = 0;

			DataMapper(QObject* Parent = nullptr){}
			~DataMapper(){}
		};
	}
}