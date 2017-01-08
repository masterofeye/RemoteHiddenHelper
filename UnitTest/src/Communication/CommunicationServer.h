#pragma once
#include "qobject.h"
#include "spdlog\spdlog.h"

class CommunicationServer :
	public QObject
{
	Q_OBJECT
private:
	/*
	@brief Instanz des Loggers
	*/
	std::shared_ptr<spdlog::logger> m_logger;
public:
	CommunicationServer(QObject *Parent = nullptr);
	~CommunicationServer();
};

