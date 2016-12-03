#pragma once

#include "qdatastream.h"
#include "Constants.h"

inline QDataStream &operator <<(QDataStream &out, const RW::CORE::Message &dataStruct)
{
    out << (quint16)dataStruct.MessageType;
    out << dataStruct.MessageSize;
    out.writeRawData(dataStruct.Message, dataStruct.MessageSize);
    out << (quint16)dataStruct.Error;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, RW::CORE::Message &dataStruct)
{
    quint16 messageType = 0;
    quint16 errorId = 0;
    dataStruct = RW::CORE::Message();
    in >> messageType;
    in >> dataStruct.MessageSize;
    dataStruct.Message.resize(dataStruct.MessageSize);
    in.readRawData(dataStruct.Message.data(), dataStruct.MessageSize);
    in >> errorId;

    dataStruct.MessageType = static_cast<RW::CORE::Util::Functions>(messageType);
	dataStruct.Error = static_cast<RW::CORE::Util::ErrorID>(errorId);
    return in;
}

inline QString GetMKSLink(QString Destination, QString MksLink)
{
	QRegExp reg("#b=\\d{1,1}.\\d{1,5}#");
	int i = reg.indexIn(MksLink);
	int ii = reg.matchedLength();
	MksLink = MksLink.replace(i + ii - 1, MksLink.count() - (i + ii - 1), "");

	QString left = MksLink.replace("#b=", "/");
	left = left.replace("#/id/", "");

	return Destination + left;
}