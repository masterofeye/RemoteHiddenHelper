#include "VoltCraft.h"

namespace RW{
	namespace HW{

		VoltCraft::VoltCraft(QObject *Parent) : PowerSupplyDevice(Parent)
		{
		}


		VoltCraft::~VoltCraft()
		{
		}

		void VoltCraft::ConfigurationChanged(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data)
		{
			if (ConfigurationReceiver::PowerSupply)
			{

			}
		}
	}
}
