#pragma once
#include "qobject.h"
#include "spdlog\spdlog.h"
#include "SQLGlobal.h"


namespace RW{
	namespace SQL{

		class RemoteWorkstation;
		class User;
		class LogEntry;
		class ElementType;
		class Product;
		class Instruction;
		class ElementConfiguration;
		class Recept;
		class Repository :
			public QObject
		{
		private:
			std::shared_ptr<spdlog::logger> m_logger;
			SourceType m_Source;
		public:
			Repository(SourceType Source, QObject* Parent = nullptr);
			~Repository();

			void InsertRemoteWorkstation(RemoteWorkstation &R);
			void InsertUser(User &U);
			void InsertElementType(ElementType &E);
			void InsertElementConfiguration(ElementConfiguration &E);
			void InsertProduct(Product &P);
			void InsertRecept(Recept &R);
			void InsertInstruction(Instruction &I);
			/*
			@brief Fügt einen LogEintray dem Repository hinzu
			@param LogEntry Logeintrag mit allen wichtigen Informationen
			*/
			void InsertLogEntry(LogEntry &E);

			bool GetRemoteWorkstationByID(quint64 ID, RemoteWorkstation& R);
			bool GetUserByID(quint64 ID, User& U);
			bool GetElementConfigurationByID(quint64 ID, ElementConfiguration& E);
			bool GetElementTypeByID(quint64 ID, ElementType& E);
			bool GetProductByID(quint64 ID, Product& P);
			bool GetInstructionByID(quint64 ID, Instruction& I);
			bool GetReceptByID(quint64 ID, Recept & R);
			bool GetLogEntryByID(quint64 ID, LogEntry& L);

			bool GetAllRemoteWorkstation(QList<RemoteWorkstation> & AllR);
			bool GetAllUser(QList<User> & AllR);
			bool GetAllElementConfiguration(QList<ElementConfiguration> & AllR);
			bool GetAllElementType(QList<ElementType> & AllR);
			bool GetAllInstruction(QList<Instruction> & AllR);
			bool GetAllRecept(QList<Recept> & AllR);
			bool GetAllProduct(QList<Product> & AllR);
			bool GetAllLogEntry(QList<LogEntry> & AllR);

			bool GetUserByName(QString Name, User& U);

		};
	}
}
