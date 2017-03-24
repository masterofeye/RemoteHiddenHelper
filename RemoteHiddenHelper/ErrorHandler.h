#pragma once
#include "qobject.h"
#include <RemoteCommunicationLibrary.h>

namespace RW{
    namespace CORE
    {
        class ErrorHandler :
            public QObject
        {
            Q_OBJECT
        private: 

            bool m_IsMKSRunning;
            bool m_IsCanEasyRunning;
            bool m_IsFHostSPRunning;
			bool m_IsPortalInfoRunning;
        public:
            ErrorHandler(QObject *Parent);
            ~ErrorHandler();


        private:
            void PrintDebugInformation();
        public:
            /**
            @brief IsBusy zeigt an ob der ErrorHandler noch dabei ist, vorangegange Prozesse zu beenden.
            */
			inline bool IsBusy(){ return m_IsMKSRunning || m_IsCanEasyRunning || m_IsFHostSPRunning || m_IsPortalInfoRunning; }

            /*
            @brief IsBusy zeigt an ob der ErrorHandler noch dabei ist, vorangegange Prozesse zu beenden. Diese Variante 
            fragt explizit nur das Modul ab welches übergeben wurde.
            */
			inline bool IsBusy(COM::MessageDescription Receiver){
     //           switch (Receiver)
     //           {
     //           case COM::MessageDescription:::
     //               return m_IsCanEasyRunning;
     //               break;
     //           case COM::MessageDescription::MKSWrapper:
     //               return m_IsMKSRunning;
     //               break;
     //           case COM::MessageDescription::FHostSPWrapper:
     //               return m_IsFHostSPRunning;
					//break;
     //           case COM::MessageDescription::PortalInfo:
					//return m_IsPortalInfoRunning;
					//break;
     //           default:
					//return true; //Als default wird immer Busy zurück gegeben
     //               break;
     //           }
            }


            inline void SetMksRunning(bool Running){ m_IsMKSRunning = Running;}
            inline void SetCanEasyRunning(bool Running){ m_IsCanEasyRunning = Running; }
            inline void SetFHostSpRunning(bool Running){ m_IsFHostSPRunning = Running; }

        public slots:
        void OnProcessMessageAnswer(COM::Message Msg);

        signals:
        void NewMessage(COM::Message Msg);
        };
    }
}
