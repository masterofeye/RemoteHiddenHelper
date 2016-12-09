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
            /*
            @brief Zeigt an, das der UsbHidLoader schon geschlossen wurde. 
            */
            bool m_IsTerminated;
            QTimer* m_Timer;

            quint64 m_ProcessID;

        public:
            UsbHidLoader(QObject* Parent = nullptr);
            ~UsbHidLoader();
            
        public slots:
        virtual void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);

        private: 
            void FlashOverUsb(QDir &BatFile);
            void CloseChildProcess(quint64 ProcessId);
        private slots:
            void AnalyseStdOutput();
            void CheckHIDState();
        signals:
            /**
            @brief Tötet den Prozess des USBHidLoaders
            */
            void KillUsbHidLoader();
            /**
            @brief Schließt die Eventloop, die für die Verarbeitung der Timerevents notwendig ist
            */
            void CloseEventLoop();
        };
    }
}