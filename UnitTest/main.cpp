
#include <QApplication>
#include <qlocalsocket.h>
#include "Unit.h"
#include "Constans.h"
#include "SQLConstructor.h"

#include "spdlog\spdlog.h"
#include "MySqlDbSink.h"
#include "Repository.h"
#include "RemoteWorkstation.h"
#include "ElementConfiguration.h"

#include <vector>  

using namespace std;


int main(int argc, char *argv[])
{


	QCoreApplication a(argc, argv);


	RW::SQL::Repository r(RW::SourceType::SQL);
	RW::SQL::RemoteWorkstation R;
	r.GetRemoteWorkstationByID(1,R);

	qDebug() << R.ID();
	qDebug() << R.Hostname();
	m_logger->error("test");

	//SQLConstructor sql;
	//sql.MySQLInitialization();



	//QLocalSocket socket;
	//socket.connectToServer("server");
	//while (!socket.isOpen());

 //   RW::CORE::Unit u(&socket);
 //   u.StartTest(RW::CORE::Util::Functions::PortalInfoShowDialog);
	return a.exec();
}


