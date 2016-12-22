#include "RemoteWorkstation.h"
#include "RemoteWorkstation_p.h"


namespace RW{
	namespace SQL{

		RemoteWorkstationPrivate::RemoteWorkstationPrivate(RemoteWorkstation *Parent) :
			QObject(Parent),
			q_ptr(Parent),
			m_Hostname(""),
			m_Mac(""),
			m_Ip(""),
			m_User(nullptr)
		{
		}

		RemoteWorkstation::RemoteWorkstation(Entity *Parent) : Entity(Parent),
			d_ptr(new RemoteWorkstationPrivate(this))
		{
		}

		RemoteWorkstation::~RemoteWorkstation()
		{
			delete d_ptr;
		}

		ElementConfiguration& RemoteWorkstation::ElementCfg()
		{ 
			Q_D(RemoteWorkstation);
			return d->m_ElementConfiguration;
		}


		void RemoteWorkstation::SetElementCfg(ElementConfiguration &ElementCfg)
		{
			Q_D(RemoteWorkstation);
			d->m_ElementConfiguration = ElementCfg;
			emit ElementCfgChanged();
		}

		User& RemoteWorkstation::CurrentUser()
		{ 
			Q_D(RemoteWorkstation);
			return d->m_User;
		}

		void RemoteWorkstation::SetCurrentUser(User &CurrentUser)
		{
			Q_D(RemoteWorkstation);
			d->m_User = CurrentUser;
			emit CurrentUserChanged();
		}

		QString RemoteWorkstation::Hostname()
		{ 
			Q_D(RemoteWorkstation);
			return d->m_Hostname;
		}
		
		void RemoteWorkstation::SetHostname(QString Hostname)
		{ 
			Q_D(RemoteWorkstation);
			d->m_Hostname = Hostname;
			emit HostnameChanged();
		}

		QString RemoteWorkstation::Mac()
		{
			Q_D(RemoteWorkstation);
			return d->m_Mac;
		}

		void RemoteWorkstation::SetMac(QString Mac)
		{ 
			Q_D(RemoteWorkstation);
			d->m_Mac = Mac;
			emit MacChanged();
		}

		QString RemoteWorkstation::Ip()
		{ 
			Q_D(RemoteWorkstation);
			return d->m_Ip;
		}

		void RemoteWorkstation::SetIp(QString Ip)
		{ 
			Q_D(RemoteWorkstation);
			d->m_Ip = Ip;
			emit IpChanged();
		}
	}
}
