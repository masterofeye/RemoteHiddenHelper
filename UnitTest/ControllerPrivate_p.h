#pragma once

#include "ConfigurationService.h"
#include "CommunicationManager.h"
#include "DeviceManager.h"

namespace RW
{
	namespace CORE
	{


		class Controller;

		class ControllerPrivate :
			public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY(ControllerPrivate)
			Q_DECLARE_PUBLIC(Controller)
		private:
			Controller* q_ptr;
		public:
			ConfigurationService* m_CfgService;
			CommunicationManager* m_CommManager;
			HW::DeviceManager* m_DeviceMananger;
		public:
			ControllerPrivate(Controller *Parent = nullptr);
			~ControllerPrivate();

		};

	}
}
