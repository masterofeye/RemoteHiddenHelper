#pragma once
#include "AbstractDevice.h"

namespace RemoteBoxWrapper
{
	class Wrapper;
}

namespace RW{
	namespace HW{

		class RemoteBoxDevice :
			public AbstractDevice
		{
			Q_OBJECT
			RemoteBoxWrapper::Wrapper* m_Wrapper;
		public:
			RemoteBoxDevice(QObject *parent = 0);
			virtual ~RemoteBoxDevice();

			bool Initialize();
			bool Reset();
			bool Shutdown();

			RemoteBoxWrapper::Wrapper* GetDevice();
		public slots:
			void RemoteBoxDevice::OnConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data);
		};
	}
}

