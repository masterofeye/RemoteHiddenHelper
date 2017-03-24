#include "UsbHidLoader.h"
#include <qfile.h>
#include <qdatastream.h>
#include <qprocess.h>
#include <qfileinfo.h>
#include <qdebug.h>
#include <qdir.h>
#include <qtimer.h>
#include <QTimerEvent>
#include <qeventloop.h>

#include <Windows.h>
#include <TlHelp32.h>

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
        const QString FLASHFINISHED2 = "Finished";
        const quint16 HIDTIMEOUT = 60000;

        UsbHidLoader::UsbHidLoader(QObject *Parent) : BasicWrapper(Parent),
            m_HIDState(false),
            m_IsTerminated(false),
            m_ProcessID(0)
        {
            m_Timer = new QTimer(this);
            connect(m_Timer, SIGNAL(timout()), this, SLOT(CheckHIDState()));
            m_Timer->start(200);
        }


        UsbHidLoader::~UsbHidLoader()
        {
        }

        void UsbHidLoader::OnProcessMessage(COM::Message Msg)
        {
			switch (Msg.MessageID())
            {
			case COM::MessageDescription::EX_UsbHidLoaderFlashFile:{

                QString file;
				file = Msg.ParameterList()[0].toString();
                // \!todo Magic Number .. der Pfad wird mehrfach verwendet
                FlashOverUsb(QDir(file));
            }
            break;
            default:
                break;
            }
        }

        void UsbHidLoader::FlashOverUsb(QDir &BatFile)
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            if (!BatFile.exists())
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLoaderFileDontExists));
                emit NewMessage(msg);
            }

            QStringList files = BatFile.entryList(QStringList(SEARCHPATTERN), QDir::Files);
            qDebug() << BatFile.absolutePath();
            QProcess proc;
            QStringList arguments;
            proc.setWorkingDirectory(BatFile.absolutePath());
            connect(&proc, &QProcess::readyReadStandardOutput, this, &UsbHidLoader::AnalyseStdOutput);
            connect(this, &UsbHidLoader::KillUsbHidLoader, &proc, &QProcess::close );

            QEventLoop evtLoop;
            connect(this, &UsbHidLoader::CloseEventLoop, &evtLoop, &QEventLoop::quit);

            proc.start(BatFile.absolutePath() + "/" + files.first());
            m_ProcessID = proc.processId();
            evtLoop.exec();

            //Aktuell landet hier keiner mehr
            if (!proc.waitForFinished(1800000))
            {
                msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLoaderFailed));
                emit NewMessage(msg);
                return;
            }

            //Nur wenn USBHidLoader nicht schon getötet wurde darf dieses Signal gesendet werden. 
            //Weil zuvor ja schon ein Fehler erkannt wurde und somit ein falscher Status verbreitet würde.
            if (m_IsTerminated)
            {
                m_IsTerminated = false;
                return;
            }

            msg.SetSuccess(false);
            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            emit NewMessage(msg);
        }


        void UsbHidLoader::AnalyseStdOutput()
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            QProcess* obj = qobject_cast<QProcess*>(sender());
            QString text = obj->readAllStandardOutput();
            QByteArray arr;
            QDataStream data(&arr, QIODevice::WriteOnly);
            data << text;

            msg.SetSuccess(true);
            msg.SetMessageID(COM::MessageDescription::EX_PrintDebugInformation);
            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
            emit NewMessage(msg);

            if (text.contains(WAITINGFORHIDPATTERN))
            {
                m_HIDState = true;
                QTimer::singleShot(HIDTIMEOUT, this, &UsbHidLoader::CheckHIDState);
                return;
                
            }
            else if (text.contains(IMX6FOUNDPATTERN))
            {
                m_HIDState = false;
                return;
            }
            else if (text.contains(CHECKSUMPATTERN))
            {
                m_IsTerminated = true;
                //Pearl Child Prozess sollte zuerst geschlossen werden
                CloseChildProcess(m_ProcessID);
                //als nächstes wird die Konsole geschlossen
                emit KillUsbHidLoader();
                //zuletzt wird der Status verschickt
                msg.SetSuccess(false);
                msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLoaderChecksum));
                emit NewMessage(msg);
                return;
            }
            else if (text.contains(TIMEOUTPATTERN))
            {
                m_IsTerminated = true;
                //Pearl Child Prozess sollte zuerst geschlossen werden
                CloseChildProcess(m_ProcessID);
                //als nächstes wird die Konsole geschlossen
                emit KillUsbHidLoader();
                //zuletzt wird der Status verschickt
                msg.SetSuccess(false);
                msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLoaderTimeOut));
                emit NewMessage(msg);
                return;
            }
            else if (text.contains(FLASHFINISHED))
            {
                m_IsTerminated = true;
                //Pearl Child Prozess sollte zuerst geschlossen werden
                CloseChildProcess(m_ProcessID);
                //als nächstes wird die Konsole geschlossen
                emit KillUsbHidLoader();
                //zuletzt wird der Status verschickt
                msg.SetSuccess(true);
                msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
                emit NewMessage(msg);
                return;
            }
            else if (text.contains(FLASHFINISHED2))
            {
                //Wenn nicht schon durch finished flashing das beeden eingeleitet wurde
                if (!m_IsTerminated)
                {
                    m_IsTerminated = true;
                    //Pearl Child Prozess sollte zuerst geschlossen werden
                    CloseChildProcess(m_ProcessID);
                    //als nächstes wird die Konsole geschlossen
                    emit KillUsbHidLoader();
                    //zuletzt wird der Status verschickt
                    msg.SetSuccess(false);
                    msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
                    msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLiaderUnknownError));
                    emit NewMessage(msg);
                }
                return;
            }
        }    

        void UsbHidLoader::CloseChildProcess(quint64 ProcessId)
        {
            // \!todo hier könnte man noch mehr nach Fehlern abfragen
            BOOL bResult;
            PROCESSENTRY32 processInfo = { sizeof(PROCESSENTRY32) };
            HANDLE hSnapShot;
            hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            bResult = Process32First(hSnapShot, &processInfo);
            while (bResult) {
                if (processInfo.th32ParentProcessID == ProcessId)
                {
                    qDebug() << "Child founded";
                    HANDLE childProcess = OpenProcess(DELETE | PROCESS_TERMINATE, DELETE, processInfo.th32ProcessID);
                    TerminateProcess(childProcess, 0);
                    CloseHandle(childProcess);
                }
                bResult = Process32Next(hSnapShot, &processInfo);
            }
            CloseHandle(hSnapShot);
        }

        void UsbHidLoader::CheckHIDState()
        {
            emit CloseEventLoop();
            if (m_HIDState)
            {
                m_IsTerminated = true;
                //Flag wieder zurück setzen
                m_HIDState = false;
                //Pearl Child Prozess sollte zuerst geschlossen werden
                CloseChildProcess(m_ProcessID);
                //als nächstes wird die Konsole geschlossen
                emit KillUsbHidLoader();
                //zuletzt wird der Status verschickt

                COM::Message msg;
                msg.SetIsExternal(true);
                msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
                msg.SetSuccess(false);
                msg.SetMessageID(COM::MessageDescription::EX_UsbHidLoaderFlashFile);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorFileUsbHidLoaderHIDState));
                return;
            }
        }
    }
}