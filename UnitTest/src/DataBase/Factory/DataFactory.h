#pragma once
#include "qobject.h"
#include "DataMapper.h"
namespace RW{
	namespace SQL{
		class DataMapper;

		class DataFactory :
			public QObject
		{
			Q_OBJECT
		public:
			DataFactory(QObject* Parent = nullptr);
			~DataFactory();
		signals :
		};
	}
}
