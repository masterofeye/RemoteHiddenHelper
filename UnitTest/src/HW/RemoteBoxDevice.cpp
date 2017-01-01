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

		bool RemoteBoxDevice::Initialize(){ return m_Wrapper->Init(); }
		bool RemoteBoxDevice::Reset(){ m_Wrapper->DeInit(); return m_Wrapper->Init(); }
		bool RemoteBoxDevice::Shutdown(){ m_Wrapper->DeInit(); return true; }

		void RemoteBoxDevice::OnConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data)
		{
			if (ConfigurationReceiver::RemoteBox == Receiver)
			{
			}
		}
	}
}