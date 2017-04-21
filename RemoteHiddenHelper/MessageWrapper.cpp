#include "MessageWrapper.h"
#include "MessageWindow.h"

namespace RW{
    namespace CORE{

        MessageWrapper::MessageWrapper(QObject* Parent) : BasicWrapper(Parent)
        {
        }


        MessageWrapper::~MessageWrapper()
        {
        }

        void MessageWrapper::OnProcessMessage(RW::COM::Message Msg)
        {
            switch (Msg.MessageID())
            {
            case COM::MessageDescription::EX_ShowPopUp:
            {
                QList<QVariant> paramlist = Msg.ParameterList();
                QString message = paramlist.at(0).toString();

                MessageWindow w;
                w.Ballon(100);
            }
            break;
            case COM::MessageDescription::EX_ShowPopUpWithTimeout:
            {       
                QList<QVariant> paramlist = Msg.ParameterList();
                QString message = paramlist.at(0).toString();
                quint64 timeout = paramlist.at(1).toULongLong();

                MessageWindow w;
                w.show();
            }
            break;
            default:
                break;
            }
        }
    }
}
