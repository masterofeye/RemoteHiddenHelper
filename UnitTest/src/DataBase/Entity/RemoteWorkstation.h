#pragma once
#include "Entity.h"
#include "qdebug.h"

namespace RW{
	namespace SQL{
		class RemoteWorkstationPrivate;
		class ElementConfiguration;
		class User;

		class RemoteWorkstation :
			public Entity
		{
			Q_OBJECT
			//Q_PROPERTY(ElementConfiguration ElementCfg READ ElementCfg WRITE SetElementCfg NOTIFY ElementCfgChanged)
			//Q_PROPERTY(User CurrentUser READ CurrentUser WRITE SetCurrentUser NOTIFY CurrentUserChanged)
			Q_PROPERTY(QString Hostname READ Hostname WRITE SetHostname NOTIFY HostnameChanged)
			Q_PROPERTY(QString Mac READ Mac WRITE SetMac NOTIFY MacChanged)
			Q_PROPERTY(QString Ip READ Ip WRITE SetIp NOTIFY IpChanged)
			Q_CLASSINFO("Version", "0.0.1")
		private:
			RemoteWorkstationPrivate* d_ptr;
			Q_DECLARE_PRIVATE(RemoteWorkstation);
		public:
			RemoteWorkstation(Entity *Parent = nullptr);
			~RemoteWorkstation();

			RemoteWorkstation(const RemoteWorkstation &R);
			RemoteWorkstation& operator=(const RemoteWorkstation &R);

			RemoteWorkstation(RemoteWorkstation &&R);
			RemoteWorkstation& operator=( RemoteWorkstation &&R);

			ElementConfiguration& ElementCfg() const;
			void SetElementCfg(ElementConfiguration &ElementCfg);
			
			User& CurrentUser() const;
			void SetCurrentUser(User &CurrentUser);

			QString Hostname() const;
			void SetHostname(QString Hostname);

			QString Mac() const;
			void SetMac(QString Mac);

			QString Ip() const;
			void SetIp(QString Ip);

		signals:
			void ElementCfgChanged();
			void CurrentUserChanged();
			void HostnameChanged();
			void MacChanged();
			void IpChanged();
		};
	}
}
