#include "Repository.h"
#include "SqlGlobal.h"

#include "AllEntities.h"

#include "DataFactory.h"
#include "DataMapper.h"


namespace RW{
	namespace SQL{
		Repository::Repository(QObject* Parent) : QObject(Parent)
		{
		}

		Repository::~Repository()
		{
		}

		void Repository::InsertRemoteWorkstation(RemoteWorkstation &R)
		{
		}

		bool Repository::GetRemoteWorkstationByID(quint64 ID, RemoteWorkstation& R)
		{
			DataFactory d;
			DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(SourceType::SQL);
			R = dm->FindByID(ID, false);
			delete dm;

			return true;
		}

		bool Repository::GetAllRemoteWorkstation(QList<RemoteWorkstation> & AllR)
		{
			DataFactory d;
			DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(SourceType::SQL);
			AllR = dm->FindAll();
			delete dm;

			return true;
		}

		void Repository::InsertLogEntry(LogEntry &E)
		{
			DataFactory d;
			DataMapper<LogEntry> *dm = d.GetMapper<LogEntry>(SourceType::SQL);
 			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertUser(User &U)
		{
			DataFactory d;
			DataMapper<User> *dm = d.GetMapper<User>(SourceType::SQL);
			dm->Insert(U);
			delete dm;
		}

		void Repository::InsertElementType(ElementType &E)
		{
			DataFactory d;
			DataMapper<ElementType> *dm = d.GetMapper<ElementType>(SourceType::SQL);
			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertElementConfiguration(ElementConfiguration &E)
		{
			DataFactory d;
			DataMapper<ElementConfiguration> *dm = d.GetMapper<ElementConfiguration>(SourceType::SQL);
			dm->Insert(E);
			delete dm;
		}

		void Repository::InsertProduct(Product &P)
		{
			DataFactory d;
			DataMapper<Product> *dm = d.GetMapper<Product>(SourceType::SQL);
			dm->Insert(P);
			delete dm;
		}

		void Repository::InsertInstruction(Instruction &I)
		{
			DataFactory d;
			DataMapper<Instruction> *dm = d.GetMapper<Instruction>(SourceType::SQL);
			dm->Insert(I);
			delete dm;
		}

	}
}