#include "ExitHandler.h"
#include <qapplication.h>

namespace RW{
    namespace CORE{

        ExitHandler::ExitHandler(QObject* Parent) : BasicWrapper(Parent)
        {
        }


        ExitHandler::~ExitHandler()
        {
        }

        void ExitHandler::OnProcessMessage(RW::COM::Message Msg)
        {
            if (Msg.IsProcessed() &&
                Msg.MessageID() == COM::MessageDescription::EX_ProcessLogout &&
                Msg.Success())
            {
                qApp->exit(0xf291);
            }
        }
    }
}