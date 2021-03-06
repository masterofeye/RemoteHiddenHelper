#include "DeviceManager.h"
#include "PowerStripeDevice.h"
#include "PowerSupplyDevice.h"
#include "RemoteBoxDevice.h"
#include "VoltCraft.h"
#include "AnelHome.h"
#include "AbstractDevice.h"

namespace RW{
	namespace HW{
		DeviceManager::DeviceManager(QObject *Parent) : QObject(Parent),
			m_DeviceList(new QMap<DeviceType, AbstractDevice*>()),
			m_logger(spdlog::get("file_logger"))
		{

		}

		void DeviceManager::SetLogger(std::shared_ptr<spdlog::logger> Logger)
		{
			m_logger = Logger;
		}

		bool DeviceManager::Init()
		{
			//TODO dies muss durch config gesetzt werden
			m_DeviceList->insert(DeviceType::PowerSupply, new VoltCraft(this));
			m_DeviceList->insert(DeviceType::RemoteBox, new RemoteBoxDevice(this));
			m_DeviceList->insert(DeviceType::PowerStripe, new AnelHome(this));

			QMapIterator<DeviceType, AbstractDevice*> i(*m_DeviceList);
			while (i.hasNext()) {
				if (!i.next().value()->Initialize())
				{
					switch (i.key())
					{
					case DeviceType::PowerSupply:
						m_logger->error("PowerSupply initialisation failed.");
						break;
					case DeviceType::RemoteBox:
						m_logger->error("RemoteBox initialisation failed.");
						break;
					case DeviceType::PowerStripe:
						m_logger->error("PowerStripe initialisation failed.");
						break;
					}				
				}
			}
			return true;
		}

		bool DeviceManager::Shutdown()
		{
			QMapIterator<DeviceType, AbstractDevice*> i(*m_DeviceList);
			while (i.hasNext()) {
				i.next().value()->Shutdown();
			}
			return true;
		}

		DeviceManager::~DeviceManager()
		{

		}

		AbstractDevice* DeviceManager::GetDevice(DeviceType Type)
		{
			return (AbstractDevice*)m_DeviceList->value(Type);
		}
	}
}