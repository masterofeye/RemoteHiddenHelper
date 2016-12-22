#pragma once
#include <qobject.h>
#include <qdatetime.h>

namespace RW{
	namespace SQL{

		class LogEntry;
		class LogEntryPrivate : public QObject
		{
			Q_OBJECT
				Q_DISABLE_COPY(LogEntryPrivate)
				Q_DECLARE_PUBLIC(LogEntry)
		private:
			LogEntry * const q_ptr;
		public: 
			QDateTime m_Date;
			QString m_Message;
			QString m_LogLevel;
			quint16 m_ThreadID;
			quint64 m_ErrorID;
			QString m_Type;
			QString m_ComputerName;

		public:
			LogEntryPrivate(LogEntry *Parent);
			~LogEntryPrivate();
		};
	}
}