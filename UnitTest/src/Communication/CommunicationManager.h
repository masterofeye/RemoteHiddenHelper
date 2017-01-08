#pragma once
#include "qobject.h"
#include "qvariant.h"
#include "spdlog\spdlog.h"

namespace RW{
	namespace CORE{

		class CommunicationManager :
			public QObject
		{
			Q_OBJECT
		private:
			/*
			@brief Instanz des Loggers
			*/
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			CommunicationManager(QObject *Parent = nullptr);
			~CommunicationManager();

		public slots: 
			void OnProcessMessage(QVariant Data);
		};
	}
}
