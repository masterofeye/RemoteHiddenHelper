#pragma once
#include "BasicWrapper.h"

QT_BEGIN_NAMESPACE
class QDir;
class QFile;
QT_END_NAMESPACE

namespace RW
{
    namespace CORE
    {
        class FileUtils :
            public BasicWrapper
        {
            Q_OBJECT
        public:
            FileUtils(QObject* Parent = nullptr);
            ~FileUtils();
        public slots:
            virtual void OnProcessMessage(COM::Message Msg);

        private:
            void Unzip(QDir &File);
            void Delete(QDir &Directory);
        };
    }
}

