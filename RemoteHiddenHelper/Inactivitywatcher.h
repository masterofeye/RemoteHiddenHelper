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
			QString m_UserName;
		public:
			explicit InactivityWatcher(QObject *parent = 0);

			
		private: 

			bool QueryActiveSession(quint64 &SessioNumber, QString Username);
			uint GetLastInputTime();
		signals:
			void UserInactive();
            void LogOff(quint64 SessioNumber);
		private slots:
            void OnLogOff(quint64 SessioNumber);
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
