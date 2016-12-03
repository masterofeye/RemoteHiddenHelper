#pragma once
#include "qobject.h"
#include "Constans.h"
#include <QStringList>

class QLocalSocket;

QDataStream &operator <<(QDataStream &out, const RW::CORE::Message &dataStruct);
QDataStream &operator >>(QDataStream &in, RW::CORE::Message &dataStruct);
QString GetMKSLink(QString Destination, QString MksLink);

const QString DESTINATION = "C:\\Temp\\";

namespace RW{
    namespace CORE{
        class Unit :
            public QObject
        {
            Q_OBJECT
        private:
            QLocalSocket* m_Socket;
		private: 
			QByteArray CreateMessage(Util::Functions Func, QByteArray Message, Util::ErrorID Id);
			void PrintDebugInformations(Message Message);
			Message GetMessage();
			void SendMessage(QByteArray Message);
			QList<FlashInfo> m_FlashFiles;
			FlashInfo m_CurrentFlashFile;
        public:
            Unit(QLocalSocket* Socket);
            ~Unit();
			void StartTest(Util::Functions StartPoint);
        public slots:
            void OnProcessMessage();
        };
    }
}


