#include "CommunicationServer.h"

#include "Util.h"


namespace RW{
	namespace CORE{


		CommunicationServer::CommunicationServer(QObject* Parent) : QLocalServer(Parent)
		{
		}


		CommunicationServer::~CommunicationServer()
		{
		}

		bool CommunicationServer::Init()
		{
			//Jeder hat Zugriff auf den Server.
			this->setSocketOptions(QLocalServer::WorldAccessOption);
			//Der Server akzeptiert nur eine Verbindung, das ist der RemoteService
			this->setMaxPendingConnections(1);

			//�berpr�fen ob schon auf Verbindungen gewartet wird.
			if(!this->isListening())
			{
				if (!this->listen("server"))
				{
					//Loggen
					return false;
				}

				//Neue Verbindungsversuche werden an diese Methode weitergeleitet.
				connect(this, &CommunicationServer::newConnection, this, &CommunicationServer::OnNewConnection);
			}
			return true;
		}

		bool CommunicationServer::DeInit()
		{
			return true;
		}

		void CommunicationServer::OnNewConnection()
		{
 			m_Client = nextPendingConnection();

			connect(m_Client, &QLocalSocket::readyRead, this, &CommunicationServer::OnDataAvailable);
			connect(m_Client, &QLocalSocket::disconnected, this, &CommunicationServer::OnClientDisconnected);
			connect(m_Client, static_cast<void(QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error), this, &CommunicationServer::OnClientSocketError);
		}

		void CommunicationServer::OnClientSocketError(QLocalSocket::LocalSocketError socketError)
		{
		}
		void CommunicationServer::OnClientDisconnected()
		{
		
		}

		void CommunicationServer::OnDataAvailable()
		{
            //! \todoist das wirklich sauber auch wenn mehrere Anfragen kommen?!
            quint64 bytes = m_Client->bytesAvailable();
            if (bytes > 0)
            {
                Message m;
                QDataStream dataStream(m_Client);
                dataStream >> m;
                emit NewMessage(m.MessageType, m.Message);
            }
		}

		void CommunicationServer::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Message)
		{
			//Nur Messages verarbeiten die auch wirklich f�r den CommunicationServer gedacht sind
			if (RW::CORE::Util::MessageReceiver::CommunicationServer == Type)
            {
                SendMessageToServer(Message);
            }
		}

		void CommunicationServer::SendMessageToServer(QByteArray Report)
		{
			if (m_Client != nullptr)
			{
                //Alle Daten in den Buffer schreiben. Ein direktes schreiben auf das Device, f�hrt dazu, das
                //Daten unvollst�ndig verschickt werden

                Message m;
                QByteArray arr;
                QDataStream dataStream2(Report);
                dataStream2 >> m;

                QDataStream dataStream(&arr,QIODevice::WriteOnly);
				dataStream << m;

				//Buffer nun an den Client �bergeben
                m_Client->write(arr);
				m_Client->flush();
			}
		}
	}
}