#pragma once
#include "Entity.h"

namespace RW
{
	namespace SQL
	{
		class LogEntryPrivate;
		class LogEntry :
			public Entity
		{
			Q_OBJECT
			Q_CLASSINFO("Version", "0.0.1")

		private:
			LogEntryPrivate *d_ptr;
			Q_DECLARE_PRIVATE(LogEntry);
		public:
			LogEntry(Entity *Parent = nullptr);
			~LogEntry();

			QDateTime Date();
			void SetDate(QDateTime);

			QString Message();
			void SetMessage(QString);

			QString LogLevel();
			void SetLogLevel(QString Level);

			quint16 ThreadID();
			void SetThreadID(quint16 ThreadID);

			quint64 ErrorID();
			void SetErrorID(quint64 ErrorID);

			QString Type();
			void SetType(QString Type);

			QString ComputerName();
			/*
			@brief Setzt den Computernamen für das aktuelle LogEntry Objekt. Der Underscore ist wichtig
			um die Methode von der Win32API zu unterscheiden.
			@param ComputerName aktueller Computername
			@return void
			*/
			void SetComputerName_(QString ComputerName);
		};

	}
}