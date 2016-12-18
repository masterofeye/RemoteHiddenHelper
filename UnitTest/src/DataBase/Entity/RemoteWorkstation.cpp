#include "RemoteWorkstation.h"

#include "ElementConfiguration.h"
#include "User.h"

namespace RW{
	namespace SQL{


		RemoteWorkstation::RemoteWorkstation(Entity *Parent) : Entity(Parent),
			m_Hostname(""),
			m_Mac(""),
			m_Ip(""),
			m_User(nullptr)
		{
		}


		RemoteWorkstation::~RemoteWorkstation()
		{
		}

		void RemoteWorkstation::SetElementCfg(ElementConfiguration &ElementCfg){ *m_ElementConfiguration = ElementCfg; emit ElementCfgChanged(); }
		void RemoteWorkstation::SetCurrentUser(User &CurrentUser){*m_User = CurrentUser; emit CurrentUserChanged();}
	}
}
