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

		/*
		@brief Schnittstelle zwischen dem Datenzugriff von Clienten und externen Datenquellen. Jeder Zugriff auf externe Datenquellen
		(File, Datenbank) muss über ein Repository erfolgen.
		*/
		class Repository :
			public QObject
		{
		private:
			/*
			@brief Instanz des Loggers
			*/
			std::shared_ptr<spdlog::logger> m_logger;

			/*
			@brief Type der aktuell verwendeteten Quelle dieses Datenmappers. Wird durch den Kontruktor gesetzt.
			*/
			SourceType m_Source;
		public:
			Repository(SourceType Source, QObject* Parent = nullptr);
			~Repository();

			/*
			@brief Fügt das übergebene RemoteWorkstation Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz, der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertRemoteWorkstation(RemoteWorkstation &R);

			/*
			@brief Fügt das übergebene User Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertUser(User &U);

			/*
			@brief Fügt das übergebene ElementType Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertElementType(ElementType &E);

			/*
			@brief Fügt das übergebene ElementConfiguration Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertElementConfiguration(ElementConfiguration &E);

			/*
			@brief Fügt das übergebene Product Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertProduct(Product &P);

			/*
			@brief Fügt das übergebene Recept Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertRecept(Recept &R);

			/*
			@brief Fügt das übergebene Instruction Objekt der Datenbank hinzu.
			@param [in] RemoteWorkstation Instanz der Daten die an die Datenbank übertragen werden sollen.
			*/
			void InsertInstruction(Instruction &I);

			/*
			@brief Fügt einen LogEintray dem Repository hinzu
			@param [in] LogEntry Logeintrag mit allen wichtigen Informationen
			*/
			void InsertLogEntry(LogEntry &E);

			/*
			@brief Liefert eine Instanz zurück die der übergebenen ID entspricht. 
			Diese Funktion liefert nur eine gültige Instanz zurück, wenn die Datenquelle die Datenbank ist.  
			@param [in] ID ID des Eintrags in der Tabelle
			@param [out] R Instanz der Remoteworkstation welche der ID entspricht
			*/
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
