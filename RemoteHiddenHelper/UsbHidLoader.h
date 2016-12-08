#pragma once
#include "BasicWrapper.h"

QT_BEGIN_NAMESPACE
class QDir;
class QTimer;
QT_END_NAMESPACE

namespace RW
{
    namespace CORE{
        class UsbHidLoader : public BasicWrapper
        {
            Q_OBJECT
        private:
            /**
            @brief Zeigt an, ob der Flashprozess aktuell auf HID aktivierung wartet
            */
            bool m_HIDState;
            QTimer* m_Timer;
        public:
            UsbHidLoader(QObject* Parent = nullptr);
            ~UsbHidLoader();
            
        public slots:
        virtual void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);

        private: 

            void SomeMethod();
            void FlashOverUsb(QDir &BatFile);

        private slots:
            void PrintDebug();
            void CheckHIDState();
        signals:
            void KillUsbHidLoader();

        protected:
            void timerEvent(QTimerEvent *event);
        };
    }
}