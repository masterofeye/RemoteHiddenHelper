#pragma once
#include <QtCore>
#include "spdlog\spdlog.h"
#include "HWGlobal.h"

namespace RW{
	namespace HW{

		class AbstractDevice;

		class DeviceManager : public QObject
		{
			Q_OBJECT
		public:
 
		private:
			std::shared_ptr<spdlog::logger> m_logger;

			QMap<DeviceType,AbstractDevice*> *m_DeviceList;

		public:
			DeviceManager(QObject *Parent = nullptr);
			virtual ~DeviceManager();

			void DeviceManager::SetLogger(std::shared_ptr<spdlog::logger> Logger);
			AbstractDevice* GetDevice(DeviceType Type);
			bool Init();
			bool Shutdown();
		};

	}
}