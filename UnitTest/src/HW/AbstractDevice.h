#pragma once
#include <QtCore>
#include "ConfigurationGlobal.h"
#include "HWGlobal.h"

namespace RW{
	namespace HW{



		class AbstractDevice : public QObject
		{
			Q_OBJECT
		private:
			QString m_DeviceName;
		public:
			AbstractDevice(QObject *parent = 0);
			~AbstractDevice();

			inline QString DeviceName(){ return m_DeviceName; }

			virtual bool Initialize() = 0;
			virtual bool Reset() = 0;
			virtual bool Shutdown() = 0;
		public slots:
		 virtual void OnConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data) = 0;
	 signals:
		 /*
		 @brief Diese Signal wird jedes mal dann ausgelöst wenn sich ein Setting geändert hat
		 @param [in] Type Der Typ gibt an, ob die Settings initial geladen wurden oder ob es sich um ein Update handelt
		 @param [in] Receiver
		 @param [in] Data Settings die sich geändert haben
		 */
		 void ConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data);
		};
	}
}