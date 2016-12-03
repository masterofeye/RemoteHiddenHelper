#include "remotehiddenhelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	RW::CORE::RemoteHiddenHelper w;
	w.show();
	return a.exec();
}
