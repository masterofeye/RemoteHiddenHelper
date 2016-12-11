
#include <QApplication>
#include <qlocalsocket.h>
#include <qdatastream.h>
#include "Unit.h"
#include "Constans.h"
#include <qregexp.h>
#include "SQLConstructor.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SQLConstructor sql;
	sql.MySQLInitialization();



	QLocalSocket socket;
	socket.connectToServer("server");
	while (!socket.isOpen());

    RW::CORE::Unit u(&socket);
    u.StartTest(RW::CORE::Util::Functions::PortalInfoShowDialog);
	return a.exec();
}


