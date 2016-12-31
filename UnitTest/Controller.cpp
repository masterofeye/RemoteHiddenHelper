#include "Controller.h"
#include "ControllerPrivate_p.h"

#include "spdlog\spdlog.h"
#include "AbstractDevive.h"


namespace RW
{
	namespace CORE
	{

		Controller::Controller(QObject *Parent) :QObject(Parent)
		{
			connect(this, &Controller::StateChanged, this, &Controller::On);
			connect(this, &Controller::StateChanged, this, &Controller::Off);
			connect(this, &Controller::StateChanged, this, &Controller::Active);
			connect(this, &Controller::StateChanged, this, &Controller::Passive);
		}

		Controller::~Controller()
		{
		}

		void Controller::On(State Source, State Target)
		{
			if (Target != State::ON)
			{
				return;
			}

			//Datenbank Zugriff prüfen


			//Logger initialisieren
			std::shared_ptr<spdlog::logger> m_logger = spdlog::create<spdlog::sinks::MySqlSink>("file_logger");

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

		}

		void Controller::Off(State Source, State Target)
		{
			if (Target != State::OFF)
			{
				return;
			}

			//HW Manager deinitialisieren
			d_ptr->m_DeviceMananger->Shutdown();
			//
			d_ptr->m_CfgService->UnregisterAll();

		}

		void Controller::Active(State Source, State Target)
		{
			if (Target != State::ACTIVE)
			{
				return;
			}


		}

		void Controller::Passive(State Source, State Target)
		{
			if (Target != State::PASSIVE)
			{
				return;
			}

			d_ptr->m_DeviceMananger->Shutdown();
		}

	}
}