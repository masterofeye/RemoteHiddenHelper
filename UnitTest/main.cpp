
#include <QApplication>
#include <qlocalsocket.h>
#include "Unit.h"
#include "Constans.h"
#include "SQLConstructor.h"

#include "InstructionFactory.h"
#include "DataMapper.h"

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


