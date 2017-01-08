#include "Controller.h"
#include "ControllerPrivate_p.h"

#include "spdlog\spdlog.h"
#include "ControllerPrivate_p.h"
#include <RemoteDataConnectLibrary.h>
#include "AbstractDevice.h"


namespace RW
{
	namespace CORE
	{
		ControllerPrivate::ControllerPrivate(Controller *Parent) : QObject(Parent),
			q_ptr(Parent)
		{

		}
		
		ControllerPrivate::~ControllerPrivate()
		{
		}


		Controller::Controller(QObject *Parent) :QObject(Parent),
			d_ptr(new ControllerPrivate(this))
		{
			connect(this, &Controller::StateChanged, this, &Controller::On);
			connect(this, &Controller::StateChanged, this, &Controller::Off);
			connect(this, &Controller::StateChanged, this, &Controller::Active);
			connect(this, &Controller::StateChanged, this, &Controller::Passive);
		}

		Controller::~Controller()
		{
		}

		void Controller::On(State Source)
		{
			m_CurrentState = State::ON;
			//Datenbank Zugriff prüfen

			//Logger initialisieren
			std::shared_ptr<spdlog::logger> m_logger = spdlog::create<spdlog::sinks::MySqlSink>("file_logger");

			if (d_ptr == nullptr)
			{
				m_logger->error("Controller isn't initialized.");
				return;
			}

			//Configuration Servive initialisieren
			d_ptr->m_CfgService = new ConfigurationService();
			
			//Communication Manager initialisieren 
			d_ptr->m_CommManager = new CommunicationManager();

			//HW Manager initialisieren
			d_ptr->m_DeviceMananger = new HW::DeviceManager();
			d_ptr->m_DeviceMananger->Init();
			//Observer starten

			d_ptr->m_CfgService->Register(d_ptr->m_DeviceMananger->GetDevice(DeviceType::RemoteBox), "");
			d_ptr->m_CfgService->Register(d_ptr->m_DeviceMananger->GetDevice(DeviceType::PowerSupply), "");
			d_ptr->m_CfgService->Register(d_ptr->m_DeviceMananger->GetDevice(DeviceType::PowerStripe), "");
			d_ptr->m_CfgService->Register(d_ptr->m_CommManager, "");


			d_ptr->m_CfgService->ReadApplicationSettings();
			d_ptr->m_CfgService->ReadUsersettings();
		}

		void Controller::Off(State Source)
		{
			m_CurrentState = State::OFF;
			//HW Manager deinitialisieren
			d_ptr->m_DeviceMananger->Shutdown();
			//
			d_ptr->m_CfgService->UnregisterAll();

		}

		void Controller::Active(State Source)
		{
			m_CurrentState = State::ACTIVE;
		}

		void Controller::Passive(State Source)
		{
			m_CurrentState = State::PASSIVE;
			d_ptr->m_DeviceMananger->Shutdown();
		}

	}
}