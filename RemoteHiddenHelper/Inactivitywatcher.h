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

			
		private: 
            bool LogOff(quint64 SessioNumber, quint16 &Error);
			bool QueryActiveSession(quint64 &SessioNumber);
			uint GetLastInputTime();
		signals:
			void UserInactive();
		private slots:
			void LogOutUser();
            void LogOutUserByTimer();
		public slots:
			void StartInactivityObservation();
			void StopInactivityObservation();
            void OnProcessMessage(COM::Message msg);
		};
	}
}
#endif // INTACTIVITYWATCHER_H
