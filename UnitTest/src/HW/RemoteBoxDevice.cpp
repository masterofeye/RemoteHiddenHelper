#include "RemoteBoxDevice.h"
#include "RemoteBoxWrapper.h"

namespace RW{
	namespace HW{

		RemoteBoxDevice::RemoteBoxDevice(QObject *Parent) : AbstractDevice(Parent),
			m_Wrapper(new RemoteBoxWrapper::Wrapper())
		{
		}


		RemoteBoxDevice::~RemoteBoxDevice()
		{
		}

		RemoteBoxWrapper::Wrapper* RemoteBoxDevice::GetDevice()
		{
			return m_Wrapper;
		}

		void RemoteBoxWrapper::ConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data)
		{
			if (ConfigurationReceiver::RemoteBox == Receiver)
			{
			}
		}
	}
}