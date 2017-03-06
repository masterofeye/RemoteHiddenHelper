#pragma once
#include <QtCore>
#include "spdlog\spdlog.h"
#include "BasicWrapper.h"

namespace RW{
	namespace CORE{
		class ShutdownHandler : public BasicWrapper
		{
			Q_OBJECT
		private:
			QThread *m_handlerThread;
			QTimer *m_ShutdownTimer;
			long long m_Timeout;

		public:
			ShutdownHandler(QObject *Parent = 0);
			~ShutdownHandler();
		private:
			bool ShutdownByWinApi();

		public slots:
			void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);
			void Shutdown();
		signals:
			void ShutdownEvt();
		public slots:
			void StartShutdownTimer(quint64 Time);
			void StopShutdownTimer();
		};
	}
}