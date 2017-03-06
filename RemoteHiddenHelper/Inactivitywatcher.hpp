#ifndef INTACTIVITYWATCHER_H
#define INTACTIVITYWATCHER_H
#include <QObject>
#include <QTimer>
#include "spdlog\spdlog.h"
#include "BasicWrapper.h"

namespace RW{

	namespace CORE{

		class InactivityWatcher : public BasicWrapper
		{
			Q_OBJECT
		private:
			std::shared_ptr<spdlog::logger> m_logger;
			QTimer *m_TimerLogout;
			long long m_Timeout;
		public:
			explicit InactivityWatcher(QObject *parent = 0);

			void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);
		private: 
			bool LogOff(quint64 SessioNumber);
			bool QueryActiveSession(quint64 &SessioNumber);
			uint GetLastInputTime();
		signals:
			void UserInactive();
		private slots:
			void LogOutUser();
		public slots:
			void StartInactivityObservation(quint64 Time);
			void StopInactivityObservation();
		};
	}
}
#endif // INTACTIVITYWATCHER_H
