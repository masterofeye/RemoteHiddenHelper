#include "RemoteWorkstation.h"
#include "RemoteWorkstation_p.h"


namespace RW{
	namespace SQL{

		RemoteWorkstationPrivate::RemoteWorkstationPrivate(RemoteWorkstation *Parent) :
			//QObject(Parent),
			q_ptr(Parent),
			m_Hostname(""),
			m_Mac(""),
			m_Ip(""),
			m_User(),
			m_ElementConfiguration()
		{
		}

		RemoteWorkstation::RemoteWorkstation(Entity *Parent) : Entity(Parent),
			d_ptr(new RemoteWorkstationPrivate(this))
		{
			qDebug() << "CTor RemoteWorkstation";
		}

		RemoteWorkstation::RemoteWorkstation(RemoteWorkstation &&R) : d_ptr(R.d_ptr)
		{
			qDebug() << "Move CTor RemoteWorkstation";
			R.d_ptr = nullptr;
		}

		RemoteWorkstation& RemoteWorkstation::operator=(RemoteWorkstation &&R)
		{
			qDebug() << "Move Operator RemoteWorkstation";
			std::swap(d_ptr, R.d_ptr);
			delete R.d_ptr;
			R.d_ptr = nullptr;
			return *this;
		}


		RemoteWorkstation::RemoteWorkstation(const RemoteWorkstation &R) :
			d_ptr(const_cast<RemoteWorkstationPrivate*>(R.d_ptr))
		{
			qDebug() << "Copy CTor RemoteWorkstation";
		}

		RemoteWorkstation& RemoteWorkstation::operator=(const RemoteWorkstation &R)
		{
			qDebug() << "Copy Operator RemoteWorkstation";
			std::swap(d_ptr, const_cast<RemoteWorkstationPrivate*>(R.d_ptr));
			return *this;
		}

		RemoteWorkstation::~RemoteWorkstation()
		{
			qDebug() << "Destructor RemoteWorkstation";
		}

		ElementConfiguration& RemoteWorkstation::ElementCfg() const
		{ 
			Q_D(const RemoteWorkstation);
			return const_cast<ElementConfiguration&>(d->m_ElementConfiguration);
		}

		void RemoteWorkstation::SetElementCfg(ElementConfiguration &ElementCfg)
		{
			Q_D(RemoteWorkstation);
			d->m_ElementConfiguration = ElementCfg;
			emit ElementCfgChanged();
		}

		User& RemoteWorkstation::CurrentUser() const
		{ 
			Q_D(const RemoteWorkstation);
			return const_cast<User&>(d->m_User);
		}

		void RemoteWorkstation::SetCurrentUser(User &CurrentUser)
		{
			Q_D(RemoteWorkstation);
			d->m_User = CurrentUser;
			emit CurrentUserChanged();
		}

		QString RemoteWorkstation::Hostname() const
		{ 
			Q_D(const RemoteWorkstation);
			return d->m_Hostname;
		}
		
		void RemoteWorkstation::SetHostname(QString Hostname)
		{ 
			Q_D(RemoteWorkstation);
			d->m_Hostname = Hostname;
			emit HostnameChanged();
		}

		QString RemoteWorkstation::Mac() const
		{
			Q_D(const RemoteWorkstation);
			return d->m_Mac;
		}

		void RemoteWorkstation::SetMac(QString Mac)
		{ 
			Q_D(RemoteWorkstation);
			d->m_Mac = Mac;
			emit MacChanged();
		}

		QString RemoteWorkstation::Ip() const
		{ 
			Q_D(const RemoteWorkstation);
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
