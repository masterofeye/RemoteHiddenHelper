#pragma once
#include "qobject.h"
#include "spdlog\spdlog.h"

#include "RemoteWorkstation.h"
#include "LogEntry.h"

namespace RW{
	namespace SQL{

		class Repository :
			public QObject
		{
		private:
			std::shared_ptr<spdlog::logger> m_logger;
		public:
			Repository(QObject* Parent = nullptr);
			~Repository();

			RemoteWorkstation Repository::GetRemoteWorkstationByID(quint64 ID);
			RemoteWorkstation Repository::GetAllRemoteWorkstation();

			/*
			@brief Fügt einen LogEintray dem Repository hinzu
			@param LogEntry Logeintrag mit allen wichtigen Informationen
			*/
			void InsertLogEntry(LogEntry E);
		};
	}
}
