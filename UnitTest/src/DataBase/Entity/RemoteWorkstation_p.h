#pragma once
#include <qobject.h>
#include "User.h"
#include "ElementConfiguration.h"

namespace RW{
	namespace SQL{

		class RemoteWorkstation;
		class ElementConfiguration;
		class RemoteWorkstationPrivate : public QObject
		{
			Q_OBJECT

				Q_DISABLE_COPY(RemoteWorkstationPrivate)
				Q_DECLARE_PUBLIC(RemoteWorkstation)
		private:
			RemoteWorkstation * const q_ptr;
		public:
			RemoteWorkstationPrivate(RemoteWorkstation *Parent);

			ElementConfiguration m_ElementConfiguration;
			User m_User;
			QString m_Hostname;
			QString m_Mac;
			QString m_Ip;

		};
	}
}
