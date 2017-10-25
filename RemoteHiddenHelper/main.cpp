#include "remotehiddenhelper.h"
#include <QtWidgets/QApplication>
#include "RemoteDataConnectLibrary.h"
#include <qdatastream.h>

//! \todo Das gehört hier eigentlich nicht hin
QDataStream &operator >>(QDataStream &in, RW::WorkstationKind &dataStruct)
{
    quint16 e;
    in >> e;
    dataStruct = (RW::WorkstationKind) e;
    return in;
}

//! \todo Das gehört hier eigentlich nicht hin
QDataStream &operator <<(QDataStream &out, const RW::WorkstationKind &dataStruct)
{
    out.startTransaction();
    out << (quint16)dataStruct;
    out.commitTransaction();
    return out;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    //Um WorkstationKInd aus einem QVariant zu holen brauchen wir das
    qRegisterMetaTypeStreamOperators<RW::WorkstationKind>("WorkstationKind");
	RW::CORE::RemoteHiddenHelper w;
	w.show();
	return a.exec();
}
