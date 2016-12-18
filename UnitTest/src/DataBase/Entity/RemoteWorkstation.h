#pragma once
#include "Entity.h"


namespace RW{
	namespace SQL{
		class ElementConfiguration;
		class User;

		class RemoteWorkstation :
			public Entity
		{
			Q_OBJECT

			Q_PROPERTY(ElementConfiguration ElementCfg MEMBER m_ElementConfiguration READ ElementCfg WRITE SetElementCfg NOTIFY ElementCfgChanged)
			Q_PROPERTY(User CurrentUser MEMBER m_User READ CurrentUser WRITE SetCurrentUser NOTIFY CurrentUserChanged)
			Q_CLASSINFO("Version", "0.0.1")
		private:

			ElementConfiguration *m_ElementConfiguration;
			User *m_User;
			QString m_Hostname;
			QString m_Mac;
			QString m_Ip;

		public:
			RemoteWorkstation(Entity *Parent = nullptr);
			~RemoteWorkstation();

			ElementConfiguration& ElementCfg(){ return *m_ElementConfiguration; }
			void SetElementCfg(ElementConfiguration &ElementCfg);
			
			User& CurrentUser(){ return *m_User; }
			void SetCurrentUser(User &CurrentUser);


			QString Hostname(){ return m_Hostname; }
			void SetHostname(QString Hostname){ m_Hostname = Hostname; emit HostnameChanged(); }

			QString Mac (){ return m_Mac; }
			void SetMac(QString Mac){ m_Mac = Mac; emit MacChanged(); }

			QString Ip(){ return m_Ip; }
			void SetIp(QString Ip){ m_Ip = Ip; emit IpChanged(); }

		signals:
			void ElementCfgChanged();
			void CurrentUserChanged();
			void HostnameChanged();
			void MacChanged();
			void IpChanged();
		};
	}
}
