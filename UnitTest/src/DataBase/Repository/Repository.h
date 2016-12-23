#pragma once
#include "qobject.h"
#include "spdlog\spdlog.h"



namespace RW{
	namespace SQL{

		class RemoteWorkstation;
		class User;
		class LogEntry;
		class ElementType;
		class Product;
		class Instruction;
		class ElementConfiguration;
		class Repository :
			public QObject
		{
		private:
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			Repository(QObject* Parent = nullptr);
			~Repository();

			void InsertRemoteWorkstation(RemoteWorkstation &R);
			void InsertUser(User &U);
			void InsertElementType(ElementType &E);
			void InsertElementConfiguration(ElementConfiguration &E);
			void InsertProduct(Product &P);
			void InsertInstruction(Instruction &I);


			bool GetRemoteWorkstationByID(quint64 ID, RemoteWorkstation& R);
			bool GetUserByID(quint64 ID, RemoteWorkstation& R)

			bool GetAllRemoteWorkstation(QList<RemoteWorkstation> & AllR);

			/*
			@brief Fügt einen LogEintray dem Repository hinzu
			@param LogEntry Logeintrag mit allen wichtigen Informationen
			*/
			void InsertLogEntry(LogEntry &E);
		};
	}
}
