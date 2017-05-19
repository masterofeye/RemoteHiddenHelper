#pragma once
#include "BasicWrapper.h"

namespace RW{
    namespace CORE{

        class ExitHandler :
            public BasicWrapper
        {
            Q_OBJECT
        public:
            ExitHandler(QObject* Parent = nullptr);
            ~ExitHandler();

            public slots:
            void OnProcessMessage(COM::Message Msg);
        };

    }
}