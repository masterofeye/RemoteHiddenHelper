#pragma once
#include "qobject.h"
#include "SqlGlobal.h"
#include "MySqlMapper.h"
#include "spdlog/spdlog.h"
namespace RW{
	namespace SQL{
		template<class T> class DataMapper;

		class DataFactory :
			public QObject
		{
			Q_OBJECT
		private: 
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			DataFactory(QObject* Parent = nullptr);
			~DataFactory();

			template<class T> DataMapper<T>* GetMapper(SourceType Source);
		signals :
		};

		template<class T> DataMapper<T>* DataFactory::GetMapper(SourceType Source)
		{
			switch (Source)
			{
			case SourceType::SQL:
				return new MySqlMapper<T>();
				break;
			case SourceType::XML:
				return nullptr;
				break;
			case SourceType::MOCK:
				return nullptr;
				break;
			default:
				return nullptr;
				break;
			}
		}
	}
}
