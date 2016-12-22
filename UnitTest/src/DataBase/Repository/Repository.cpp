#include "Repository.h"
#include "SqlGlobal.h"

#include "RemoteWorkstation.h"
#include "ElementConfiguration.h"
#include "ElementType.h"
#include "User.h"
#include "Recept.h"
#include "Product.h"
#include "Instruction.h"

#include "DataFactory.h"
#include "DataMapper.h"
#include "LogEntry.h"

namespace RW{
	namespace SQL{
		Repository::Repository(QObject* Parent) : QObject(Parent)
		{
		}

		 Repository::~Repository()
		{
		}

		RemoteWorkstation Repository::GetRemoteWorkstationByID(quint64 ID)
		{
			DataFactory d;
			DataMapper<RemoteWorkstation> *dm = d.GetMapper<RemoteWorkstation>(SourceType::SQL);
			RemoteWorkstation rw = dm->FindByID(ID);
			delete dm;
			return rw;
		}


		void Repository::InsertLogEntry(LogEntry E)
		{
			DataFactory d;
			DataMapper<LogEntry> *dm = d.GetMapper<LogEntry>(SourceType::SQL);
 			dm->Insert(E);
			delete dm;
		}

	}
}