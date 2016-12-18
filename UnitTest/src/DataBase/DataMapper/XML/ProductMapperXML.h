#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class ProductMapperXML :
			public DataMapper
		{
			Q_OBJECT
		public:
			ProductMapperXML(DataMapper *Parent = nullptr);
			~ProductMapperXML();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};
	}
}