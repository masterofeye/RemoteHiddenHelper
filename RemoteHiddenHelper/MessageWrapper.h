#pragma once
#include "BasicWrapper.h"

namespace RW{
    namespace CORE{

        class MessageWrapper : public BasicWrapper
        {
            Q_OBJECT
        public:
            MessageWrapper(QObject* Parent = nullptr);
            ~MessageWrapper();
        public slots:
        /**
        @brief Es muss nicht noch mal geprüft ob die Anzahl der parameter stimmt, weil dies durch den Server schon geschieht.
        */
            void OnProcessMessage(COM::Message Msg);

        };
    }
}

