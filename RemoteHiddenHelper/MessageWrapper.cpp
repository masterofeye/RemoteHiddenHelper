#include "MessageWrapper.h"
#include "MessageWindow.h"

namespace RW{
    namespace CORE{

        MessageWrapper::MessageWrapper(QObject* Parent) : BasicWrapper(Parent)
        {
           m_Window = new MessageWindow();
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
                quint8 index = paramlist.at(1).toInt();

                m_Window->Ballon(0, message, index );
            }
            break;
            case COM::MessageDescription::EX_ShowPopUpWithTimeout:
            {       
                QList<QVariant> paramlist = Msg.ParameterList();
                QString message = paramlist.at(0).toString();
                quint64 timeout = paramlist.at(1).toULongLong();
                quint8 index = paramlist.at(1).toInt();

                m_Window->Ballon(timeout, message, index);
            }
            break;
            default:
                break;
            }
        }
    }
}
