#pragma once
#include "qobject.h"
#include "SqlGlobal.h"
#include "MySqlMapper.h"
#include "spdlog/spdlog.h"
namespace RW{
	namespace SQL{
		template<class T> class DataMapper;

		/*Abstrahiert die Erzeugung der Datenquelle durch eine Factory Klasse. Sobald eine neue Datenquelle 
		inzugefügt wird, muss diese Schnittelle um den Type der Datenquelle erweitert werden.*/
		class DataFactory :
			public QObject
		{
			Q_OBJECT
		private: 
			/*
			@brief Instanz des Loggers
			*/
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			DataFactory(QObject* Parent = nullptr) : QObject(Parent){}
			~DataFactory(){}

			/*
			@brief Erzeugt einen DataMapper mit der angegbene Datenquelle. Für das löschen des Objektes ist 
			der Aufrufer verantwortlich.
			@oaram Source Type der Quelle z.b. Datenbank oder File
			*/
			template<class T> DataMapper<T>* GetMapper(SourceType Source);
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
