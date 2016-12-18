#pragma once
#include "DataMapper.h"

namespace RW{
	namespace SQL{

		class InstructionMapperSQL : public DataMapper
		{
			Q_OBJECT
		public:
			InstructionMapperSQL(DataMapper *Parent = nullptr);
			~InstructionMapperSQL();

			virtual bool Insert(const Entity &Data);
			virtual bool Update(const Entity &Data);
			virtual Entity&& FindByID(const quint64 id);
			virtual QList<Entity>&& FindAll();
		};

	}
}