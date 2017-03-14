#pragma once
#include <qlocalsocket.h>
#include <qdatastream.h>

#include "Constants.h"

namespace RW{
	namespace CORE{
		const QString SocketName = "remotehiddenhelper";

		class CommunicationServer :
			public QObject
		{
			Q_OBJECT
		private: 
			QLocalSocket* m_Client;
		public:
			CommunicationServer(QObject* Parent = nullptr);
			~CommunicationServer();

			bool Init();
			bool DeInit();
		public slots:
			void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Message);
            void SendIdentifier();
		private: 
			void OnClientDisconnected();
			void OnClientSocketError(QLocalSocket::LocalSocketError socketError);
			void OnDataAvailable();

            void SendMessageToServer(QByteArray Report);
		 signals:
			void NewMessage(Util::Functions MessageType, QByteArray Message);
		};


	}
}

