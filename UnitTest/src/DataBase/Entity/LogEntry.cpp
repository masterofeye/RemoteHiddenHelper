#include "LogEntry.h"
#include "LogEntry_p.h"
#include "qdebug.h"

namespace RW{
	namespace SQL{

		LogEntryPrivate::LogEntryPrivate(LogEntry* Parent) :
			QObject(Parent),
			q_ptr(Parent),
			m_ComputerName(""),
			m_Date(QDateTime::currentDateTime()),
			m_ErrorID(0),
			m_LogLevel(""),
			m_Message(""),
			m_ThreadID(0),
			m_Type("")
		{

		}

		LogEntryPrivate::~LogEntryPrivate()
		{
		}

		LogEntry::LogEntry(Entity *Parent) : Entity(Parent),
			d_ptr(new LogEntryPrivate(this))
		{
		}


		LogEntry::~LogEntry()
		{
		}

		QDateTime LogEntry::Date()
		{
			Q_D(LogEntry);
			return d->m_Date;
		}

		void LogEntry::SetDate(QDateTime Date)
		{
			Q_D(LogEntry);
			d->m_Date = Date;
		}

		QString LogEntry::Message()
		{
			Q_D(LogEntry);
			return d->m_Message;
		}

		void LogEntry::SetMessage(QString Message)
		{
			Q_D(LogEntry);
			d->m_Message = Message;
		}


		QString LogEntry::LogLevel()
		{
			Q_D(LogEntry);
			return d->m_LogLevel;
		}
		void LogEntry::SetLogLevel(QString Level)
		{
			Q_D(LogEntry);
			d->m_LogLevel = Level;
		}

		quint16 LogEntry::ThreadID()
		{
			Q_D(LogEntry);
			return d->m_ThreadID;
		}
		void LogEntry::SetThreadID(quint16 ThreadID)
		{
			Q_D(LogEntry);
			d->m_ThreadID = ThreadID;
		}

		quint64 LogEntry::ErrorID()
		{
			Q_D(LogEntry);
			return d->m_ErrorID;
		}
		void LogEntry::SetErrorID(quint64 ErrorID)
		{
			Q_D(LogEntry);
			d->m_ErrorID;
		}

		QString LogEntry::Type()
		{
			Q_D(LogEntry);
			return d->m_Type;
		}
		void LogEntry::SetType(QString Type)
		{
			Q_D(LogEntry);
			d->m_Type = Type;
		}

		QString LogEntry::ComputerName()
		{
			Q_D(LogEntry);
			return d->m_ComputerName;
		}


		void LogEntry::SetComputerName_(QString ComputerName)
		{
			Q_D(LogEntry);
			d->m_ComputerName = ComputerName;
		}
	}
}