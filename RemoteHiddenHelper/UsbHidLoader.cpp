#include "UsbHidLoader.h"
#include <qfile.h>
#include <qdatastream.h>
#include <qprocess.h>
#include <qfileinfo.h>
#include <qdebug.h>
#include <qdir.h>
#include <qtimer.h>
#include <QTimerEvent>

namespace RW
{
    namespace CORE
    {
        const QString SEARCHPATTERN = "*.bat";
        const QString WAITINGFORHIDPATTERN = "waiting for HID";
        const QString IMX6FOUNDPATTERN = "IMX6 HID device found";
        const QString CHECKSUMPATTERN = "!!! CHECKSUM ERROR";
        const QString TIMEOUTPATTERN = "ERROR : operation canceled due to timeout";
        const QString FLASHFINISHED = "finished flashing";


        UsbHidLoader::UsbHidLoader(QObject *Parent) : BasicWrapper(Parent),
            m_HIDState(false)
        {
            m_Timer = new QTimer(this);
            connect(m_Timer, SIGNAL(timout()), this, SLOT(CheckHIDState()));
            m_Timer->start(200);
        }


        UsbHidLoader::~UsbHidLoader()
        {
        }

        void UsbHidLoader::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
        {
            if (Type == Util::MessageReceiver::UsbHidLoader)
            {
                switch (Func)
                {
                case RW::CORE::Util::Functions::UsbHidLoaderFlashFile:{

                    QString file;
                    QDataStream data(Report);
                    data >> file;
                    // \!todo Magic Number .. der Pfad wird mehrfach verwendet
                    FlashOverUsb(QDir(file));
                }
                break;
                default:
                    break;
                }
            }
        }

        void UsbHidLoader::FlashOverUsb(QDir &BatFile)
        {
            if (!BatFile.exists())
            {
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFileDontExists, "");
            }

            QStringList files = BatFile.entryList(QStringList(SEARCHPATTERN), QDir::Files);
            qDebug() << BatFile.absolutePath();
            QProcess proc;
            QStringList arguments;
            proc.setWorkingDirectory(BatFile.absolutePath());
            connect(&proc, &QProcess::readyReadStandardOutput, this, &UsbHidLoader::PrintDebug);
            connect(this, &UsbHidLoader::KillUsbHidLoader, &proc, &QProcess::kill );



            proc.start(BatFile.absolutePath() + "/" + files.first());
            if (!proc.waitForFinished(1800000))
            {
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
            emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::Success, "");
        }


        void UsbHidLoader::PrintDebug()
        {
            QProcess* obj = qobject_cast<QProcess*>(sender());
            QString text = obj->readAllStandardOutput();
            qDebug() << text;

            if (text.contains(WAITINGFORHIDPATTERN))
            {
                m_HIDState = true;
                SomeMethod();
                return;
                
            }
            else if (text.contains(IMX6FOUNDPATTERN))
            {
                m_HIDState = false;
                return;
            }
            else if (text.contains(CHECKSUMPATTERN))
            {
                emit KillUsbHidLoader();
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
            else if (text.contains(TIMEOUTPATTERN))
            {
                emit KillUsbHidLoader();
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
            else if (text.contains(FLASHFINISHED))
            {
                emit KillUsbHidLoader();
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
        }

        void UsbHidLoader::timerEvent(QTimerEvent *event)
        {
            if (m_HIDState)
            {
                emit KillUsbHidLoader();
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
        }

        void UsbHidLoader::CheckHIDState()
        {
            if (m_HIDState)
            {
                emit KillUsbHidLoader();
                emit NewMessage(Util::Functions::UsbHidLoaderFlashFile, Util::ErrorID::ErrorFileUsbHidLoaderFailed, "");
                return;
            }
        }

        void UsbHidLoader::SomeMethod()
        {

            m_Timer->setSingleShot(true); // if you only want it to fire once
            m_Timer->start(1000);
        }
    }
}