#pragma once
#include "AbstractDevice.h"

namespace RW{
	namespace HW{

		class PowerStripeDevice :
			public AbstractDevice
		{
			Q_OBJECT
		public:
			PowerStripeDevice(QObject *parent = 0);
			~PowerStripeDevice();

			virtual bool SwitchPort(quint8 Port, SwitchState St) = 0;
			virtual bool SwitchAll(SwitchState St) = 0;
			virtual bool GetPortState(quint8 Port, SwitchState &St) = 0;
		};
	}
}