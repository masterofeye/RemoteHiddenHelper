
#include <QApplication>
#include <qlocalsocket.h>
#include "Unit.h"
#include "Constans.h"
#include "SQLConstructor.h"

#include "spdlog\spdlog.h"
#include "MySqlDbSink.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	std::shared_ptr<spdlog::logger> m_logger = spdlog::create<spdlog::sinks::MySqlSink>("file_logger");
	m_logger->error("test");

	SQLConstructor sql;
	sql.MySQLInitialization();



	QLocalSocket socket;
	socket.connectToServer("server");
	while (!socket.isOpen());

    RW::CORE::Unit u(&socket);
    u.StartTest(RW::CORE::Util::Functions::PortalInfoShowDialog);
	return a.exec();
}


