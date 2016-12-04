
#include <QApplication>
#include <qlocalsocket.h>
#include <qdatastream.h>
#include "Unit.h"
#include "Constans.h"
#include <qregexp.h>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QLocalSocket socket;
	socket.connectToServer("server");
	while (!socket.isOpen());

    RW::CORE::Unit u(&socket);
    u.StartTest(RW::CORE::Util::Functions::PortalInfoShowDialog);
	return a.exec();
}


