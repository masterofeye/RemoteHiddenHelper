#pragma once
#include "BasicWrapper.h"


class MessageWindow;

namespace RW{
    namespace CORE{

        class MessageWrapper : public BasicWrapper
        {
            Q_OBJECT
        private:
            MessageWindow *m_Window = nullptr;
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

