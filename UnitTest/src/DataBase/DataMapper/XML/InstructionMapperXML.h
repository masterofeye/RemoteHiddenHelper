#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class InstructionMapperXML :
			public DataMapper
		{
			Q_OBJECT
		public:
			InstructionMapperXML(DataMapper *Parent = nullptr);
			~InstructionMapperXML();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};
	}
}