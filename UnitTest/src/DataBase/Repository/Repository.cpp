#include "Repository.h"
#include "SqlGlobal.h"

#include "AllEntities.h"

#include "DataFactory.h"
#include "DataMapper.h"


namespace RW{
	namespace SQL{
		Repository::Repository(SourceType Source, QObject* Parent) : QObject(Parent),
			m_Source(Source)
		{
		}

		Repository::~Repository()
		{
		}

		void Repository::InsertRemoteWorkstation(RemoteWorkstation &R)
		{
			DataFactory d;
			DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(m_Source);
			dm->Insert(R);
			delete dm;
		}

		void Repository::InsertLogEntry(LogEntry &E)
		{
			DataFactory d;
			DataMapper<LogEntry> *dm = d.GetMapper<LogEntry>(m_Source);
 			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertUser(User &U)
		{
			DataFactory d;
			DataMapper<User> *dm = d.GetMapper<User>(m_Source);
			dm->Insert(U);
			delete dm;
		}

		void Repository::InsertElementType(ElementType &E)
		{
			DataFactory d;
			DataMapper<ElementType> *dm = d.GetMapper<ElementType>(m_Source);
			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertElementConfiguration(ElementConfiguration &E)
		{
			DataFactory d;
			DataMapper<ElementConfiguration> *dm = d.GetMapper<ElementConfiguration>(m_Source);
			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertProduct(Product &P)
		{
			DataFactory d;
			DataMapper<Product> *dm = d.GetMapper<Product>(m_Source);
			dm->Insert(P);
			delete dm;
		}

		void Repository::InsertInstruction(Instruction &I)
		{
			DataFactory d;
			DataMapper<Instruction> *dm = d.GetMapper<Instruction>(m_Source);
			dm->Insert(I);
			delete dm;
		}

		void Repository::InsertRecept(Recept &R)
		{
			DataFactory d;
			DataMapper<Recept> *dm = d.GetMapper<Recept>(m_Source);
			dm->Insert(R);
			delete dm;
		}

		bool Repository::GetRemoteWorkstationByID(quint64 ID, RemoteWorkstation& R)
		{
			try{
				DataFactory d;
				DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(m_Source);
				R = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetRemoteWorkstationByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetUserByID(quint64 ID, User& U)
		{
			try{
				DataFactory d;
				DataMapper<User> *dm = d.GetMapper<User>(m_Source);
				U = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetUserByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetElementConfigurationByID(quint64 ID, ElementConfiguration& E)
		{
			try{
				DataFactory d;
				DataMapper<ElementConfiguration> *dm = d.GetMapper<ElementConfiguration>(m_Source);
				E = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetElementConfigurationByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetElementTypeByID(quint64 ID, ElementType& E)
		{
			try{
				DataFactory d;
				DataMapper<ElementType> *dm = d.GetMapper<ElementType>(m_Source);
				E = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetElementConfigurationByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetProductByID(quint64 ID, Product& P)
		{
			try{
				DataFactory d;
				DataMapper<Product> *dm = d.GetMapper<Product>(m_Source);
				P = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetProductByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetInstructionByID(quint64 ID, Instruction& I)
		{
			try{
				DataFactory d;
				DataMapper<Instruction> *dm = d.GetMapper<Instruction>(m_Source);
				I = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetInstructionByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetReceptByID(quint64 ID, Recept & R)
		{
			try{
				DataFactory d;
				DataMapper<Recept> *dm = d.GetMapper<Recept>(m_Source);
				R = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetReceptByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetLogEntryByID(quint64 ID, LogEntry& L)
		{
			try{
				DataFactory d;
				DataMapper<LogEntry> *dm = d.GetMapper<LogEntry>(m_Source);
				L = dm->FindByID(ID, false);
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetLogEntryByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllRemoteWorkstation(QList<RemoteWorkstation> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetLogEntryByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllUser(QList<User> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<User> *dm = d.GetMapper<User>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetLogEntryByID throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllElementConfiguration(QList<ElementConfiguration> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<ElementConfiguration> *dm = d.GetMapper<ElementConfiguration>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllElementConfiguration throwed a exception");
				return false;
			}
			return true;
		}


		bool Repository::GetAllElementType(QList<ElementType> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<ElementType> *dm = d.GetMapper<ElementType>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllElementType throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllInstruction(QList<Instruction> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<Instruction> *dm = d.GetMapper<Instruction>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllInstruction throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllRecept(QList<Recept> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<Recept> *dm = d.GetMapper<Recept>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllRecept throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllProduct(QList<Product> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<Product> *dm = d.GetMapper<Product>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllProduct throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetAllLogEntry(QList<LogEntry> & AllR)
		{
			try{
				DataFactory d;
				DataMapper<LogEntry> *dm = d.GetMapper<LogEntry>(m_Source);
				AllR = dm->FindAll();
				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetAllLogEntry throwed a exception");
				return false;
			}
			return true;
		}

		bool Repository::GetUserByName(QString Name, User& U)
		{
			QList<User> list;
			try{
				DataFactory d;
				DataMapper<User> *dm = d.GetMapper<User>(m_Source);
				list = dm->FindAll();
				for each (auto var in list)
				{
					if (var.UserName() == Name)
						U = var;
				}

				delete dm;
			}
			catch (...)
			{
				m_logger->emerg("GetUserByID throwed a exception");
				return false;
			}
			return true;
		}
	}
}