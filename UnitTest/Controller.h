#pragma once
#include "qobject.h"
#include "HWGlobal.h"
#include "spdlog\spdlog.h"

namespace RW
{
	namespace CORE
	{
		enum class State
		{
			ON,
			OFF,
			PASSIVE,
			ACTIVE

		};

		class ControllerPrivate;
		class Controller :
			public QObject
		{
			Q_OBJECT
		private:
			ControllerPrivate *d_ptr;
			Q_DECLARE_PRIVATE(Controller);

			State m_CurrentState;

			/*
			@brief Instanz des Loggers
			*/
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			Controller(QObject *Parent = nullptr);
			~Controller();

			void On(State Source);
			void Off(State Source);
			void Passive(State Source);
			void Active(State Source);

		signals:
			void StateChanged(State Source, State Target);
		};

	}
}
