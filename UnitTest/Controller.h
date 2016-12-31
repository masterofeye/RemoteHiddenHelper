#pragma once

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

		enum class DeviceType
		{
			RemoteBox,
			PowerStripe,
			PowerSupply,
		};

		class Controller :
			public QObject
		{
		private:
			ControllerPrivate *d_ptr;
			Q_DECLARE_PRIVATE(RemoteWorkstation);
		public:
			Controller(QObject *Parent = nullptr);
			~Controller();

			void On(State Source, State Target);
			void Off(State Source, State Target);
			void Passive(State Source, State Target);
			void Active(State Source, State Target);

		signals:
			void StateChanged(State Source, State Target);
		};

	}
}
