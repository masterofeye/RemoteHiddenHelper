#include "RemoteWorkstationMapperXML.h"
#include "RemoteWorkstation.h"

namespace RW{
	namespace SQL{

		RemoteWorkstationMapperXML::RemoteWorkstationMapperXML(DataMapper *Parent) : DataMapper(Parent)
		{
		}


		RemoteWorkstationMapperXML::~RemoteWorkstationMapperXML()
		{
		}


		bool RemoteWorkstationMapperXML::Insert(const Entity &Data)
		{
			return false;
		}

		bool RemoteWorkstationMapperXML::Update(const Entity &Data)
		{
			return false;
		}

		Entity&& RemoteWorkstationMapperXML::FindByID(const quint64 id)
		{
			RemoteWorkstation e;

			return std::move(e);
		}

		QList<Entity>&& RemoteWorkstationMapperXML::FindAll()
		{
			QList<Entity> l;

			return std::move(l);
		}
	}
}