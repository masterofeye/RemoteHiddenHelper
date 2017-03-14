#include "CommunicationServer.h"

#include "Util.h"


namespace RW{
	namespace CORE{


		CommunicationServer::CommunicationServer(QObject* Parent) : QObject(Parent),
			m_Client(new QLocalSocket(this))
		{
		}


		CommunicationServer::~CommunicationServer()
		{
		}

		bool CommunicationServer::Init()
		{
			m_Client->abort();

            connect(m_Client, &QLocalSocket::connected, this, &CommunicationServer::SendIdentifier);
            connect(m_Client, &QLocalSocket::readyRead, this, &CommunicationServer::OnDataAvailable);
            connect(m_Client, &QLocalSocket::disconnected, this, &CommunicationServer::OnClientDisconnected);
            connect(m_Client, static_cast<void(QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error), this, &CommunicationServer::OnClientSocketError);

			m_Client->connectToServer("Server");
			return true;
		}

        void CommunicationServer::SendIdentifier()
        {
            if (m_Client->isValid() && m_Client->isOpen())
            {
                QByteArray m;
                m.append("identifier=remotehiddenhelper");
                quint64 written = m_Client->write(m);
                bool flush = m_Client->flush();
            }
        }

		bool CommunicationServer::DeInit()
		{
			return true;
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
                emit NewMessage(m.MessageFunc, m.Message);
            }
		}

		void CommunicationServer::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Message)
		{
			//Nur Messages verarbeiten die auch wirklich für den CommunicationServer gedacht sind
			if (RW::CORE::Util::MessageReceiver::CommunicationServer == Type)
            {
                SendMessageToServer(Message);
            }
		}

		void CommunicationServer::SendMessageToServer(QByteArray Report)
		{
			if (m_Client != nullptr)
			{
                //Alle Daten in den Buffer schreiben. Ein direktes schreiben auf das Device, führt dazu, das
                //Daten unvollständig verschickt werden

                Message m;
                QByteArray arr;
                QDataStream dataStream2(Report);
                dataStream2 >> m;

                QDataStream dataStream(&arr,QIODevice::WriteOnly);
				dataStream << m;

				//Buffer nun an den Client übergeben
                m_Client->write(arr);
				m_Client->flush();
			}
		}
	}
}