#include "AnelHome.h"


namespace RW{
	namespace HW{

		AnelHome::AnelHome(QObject *parent) : PowerStripeDevice(parent),
			m_SendSocket(new QUdpSocket(this)),
			m_ReceiveSocket(new QUdpSocket(this))
		{
			m_Sockets = new Device_Socket[8];

			m_IpAddress = QHostAddress::Any;
		}

		AnelHome::~AnelHome()
		{
			delete[] m_Sockets;
		}

		bool AnelHome::Initialize()
		{
			if (m_ReceiveSocket->bind(PORT_RECEIVE, QUdpSocket::ShareAddress))
			{

				connect(m_ReceiveSocket, &QUdpSocket::readyRead, this, &AnelHome::ReceiveAsk);
				if (m_ReceiveSocket->open(QIODevice::OpenModeFlag::ReadOnly))
				{
					
					if (m_SendSocket->bind(QHostAddress::Any, PORT_SEND, QUdpSocket::ShareAddress))
					{

					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
			else
			{
				return false;
			}

			SendAsk(PORT_SEND, "wer da?");
			return true;
		}


		QString AnelHome::MapState(SwitchState Command)
		{
			if (Command == SwitchState::ON)
				return "Sw_on";
			else if (Command == SwitchState::OFF)
				return "Sw_off";
			else
				return  "";
		}

		void AnelHome::Switch(SwitchState Command, int Socket)
		{
			m_SendSocket->open(QIODevice::OpenModeFlag::WriteOnly);
			QString cmd = MapState(Command) + QString(Socket) + m_User + m_Password;
			m_SendSocket->write(QByteArray(cmd.toUtf8()));
			m_SendSocket->close();
		}

		void AnelHome::SwitchAll(SwitchState Command, int Sockets)
		{
			m_SendSocket->open(QIODevice::OpenModeFlag::WriteOnly);
			QString cmd = MapState(Command) + QString(Sockets) + m_User + m_Password;
			m_SendSocket->write(QByteArray(cmd.toUtf8()));
			m_SendSocket->close();
		}


		void AnelHome::Parse(QByteArray Message)
		{
			QStringList splittedList = QString(Message).split(":");
			if (splittedList[0] != "NET-PwrCtrl") return;

			//Error wrong User;Pass
			if (splittedList[2] == "NoPass")
			{
				//NoPass = buf_split[1]; //NoPass=Hostname else NoPass=empty string
				return;
			}

			m_Dev.Host_Name = splittedList[1];
			m_Dev.IP = QHostAddress(splittedList[2]);
			m_Dev.Mask = QHostAddress(splittedList[3]);
			m_Dev.Gateway = QHostAddress(splittedList[4]);
			m_Dev.MAC = splittedList[5];

			for (int i = 0; i < 8; i++)
			{
				QStringList name_split = splittedList[6 + i].split(',');
				m_Sockets[i].Socket_Name = name_split[0];
				m_Sockets[i].Socket_State = name_split[1].toInt();
			}

			m_Dev.Blocked = splittedList[14].toUtf8();
			m_Dev.HTTP_Port = splittedList[15].toInt();
			m_Dev.Temperatur = -127;
		}

		void AnelHome::SendAsk(int SenderPort, QString Command)
		{
			
			m_SendSocket->connectToHost("192.168.0.25", SenderPort);

			m_SendSocket->open(QIODevice::OpenModeFlag::WriteOnly);
			m_SendSocket->write(QByteArray(Command.toUtf8()));
			m_SendSocket->close();
		}

		void AnelHome::ReceiveAsk()
		{
			QByteArray answer = m_ReceiveSocket->readAll();
			Parse(answer);
		}

		/*
		@todo Need to be implemented
		*/
		bool AnelHome::Reset()
		{
			return true;
		}

		/*
		@todo Need to be implemented
		*/
		bool AnelHome::Shutdown()
		{
			return true;
		}

		bool AnelHome::SwitchPort(quint8 Port, SwitchState St)
		{
			Switch(St, Port);
			//TODO Auswertung fehlt
			return true;
		}

		bool AnelHome::SwitchAll(SwitchState St)
		{
			SwitchAll(St,3);
			//TODO Auswertung fehlt
			return true;
		}

		bool AnelHome::GetPortState(quint8 Port, SwitchState &St)
		{
			St = m_Sockets[Port].Socket_State == true ? SwitchState::ON : SwitchState::OFF;
			return true;
		}

		void AnelHome::OnConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data)
		{
			if (ConfigurationReceiver::PowerSupply == Receiver)
			{
			}
		}

	}
}