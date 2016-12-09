#include "Unit.h"
#include <qlocalserver.h>
#include <qdatastream.h>
#include <qdebug.h>
#include <QMetaEnum>
#include <qlocalsocket.h>
#include <qmessagebox.h>
#include <qdir.h>

namespace RW{
    namespace CORE{
        Unit::Unit(QLocalSocket* Socket) : m_Socket(Socket)
        {
            QObject::connect(m_Socket, &QLocalSocket::readyRead, this, &RW::CORE::Unit::OnProcessMessage);
        }

        Unit::~Unit()
        {
        }

        void Unit::StartTest(Util::Functions StartPoint)
        {
            QByteArray block = CreateMessage(StartPoint, "", Util::ErrorID::Success);
            m_Socket->write(block);
            m_Socket->flush();
        }

        QByteArray Unit::CreateMessage(Util::Functions Func, QByteArray Message, Util::ErrorID Id)
        {
            QByteArray arr;
            RW::CORE::Message m(Func, Message.size(), Message, Id);
            QDataStream in(&arr, QIODevice::WriteOnly);
            in.setVersion(QDataStream::Qt_5_7);
            in << m;
            return arr;
        }

        void Unit::PrintDebugInformations(Message Message)
        {
            //Aktuelle Werte ausgeben
            qDebug() << "Aktuell wurde der Schritt: " << QVariant::fromValue(Message.MessageType).toString() << " ausgeführt.";
            //qDebug() << "Message: " << Message.Message;
            qDebug() << "Der Arbeitsschritt wurde mit " << QVariant::fromValue(Message.Error).toString() << " abgeschlossen.";
            qDebug() << "#################################################################################";
        }

        Message Unit::GetMessage()
        {
            Message m;
            QDataStream in((QIODevice*)m_Socket);
            in >> m;
            return m;
        }

        void Unit::SendMessage(QByteArray Message)
        {
            m_Socket->write(Message);
            m_Socket->flush();
        }

        void Unit::ToogleCL30Slow(QByteArray Message)
        {
            qDebug() << "ToogleSlow";
            if (Message.size() > 0)
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPGetProgress, "", Util::ErrorID::Success);
                SendMessage(arr);
            }
        }
        void Unit::ToogleCL30Fast(QByteArray Message)
        {
            qDebug() << "ToogleFast";
            if (Message.size() > 0)
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPGetState, "", Util::ErrorID::Success);
                SendMessage(arr);
            }
        }


        void Unit::OnProcessMessage()
        {
			Message m = GetMessage();
            
            if (m.MessageType == Util::Functions::PrintDebugInformation)
            {
                QString informatiom;
                QDataStream data(m.Message);
                data >> informatiom;

                qDebug() << informatiom;
                return;
            }


			PrintDebugInformations(m);

            if (m.Error != Util::ErrorID::Success)
            {
                m_Socket->disconnect();
                QMessageBox msgBox;
				msgBox.setText("Hat einen Fehler festgestellt. " + QVariant::fromValue(m.Error).toString());
                msgBox.exec();
                return;

            }

            if (m.Error == Util::ErrorID::Busy)
            {
                m_Socket->disconnect();
                QMessageBox msgBox;
                msgBox.setText("Hiddenhelper is Busy.");
                msgBox.exec();
                return;
            }

            switch (m.MessageType)
            {
            case Util::Functions::CanEasyStartApplication:
            {
                QByteArray arr;
                if (m_CurrentFlashFile.FlashType == Util::FlashType::GC)
                {
                    arr = CreateMessage(Util::Functions::CanEasyLoadWorkspace, QString("C:\\Arbeitsbereiche_PF3\\Arbeitsbereich_BR213_V4.50\\W213\\CanEasyBR213_V4.50.csm").toUtf8(), Util::ErrorID::Success);
                }
                else if (m_CurrentFlashFile.FlashType == Util::FlashType::AC || m_CurrentFlashFile.FlashType == Util::FlashType::Bootloader)
                {
                    arr = CreateMessage(Util::Functions::CanEasyLoadWorkspace, QString("C:\\Arbeitsbereiche_PF3\\Flashen.csm").toUtf8(), Util::ErrorID::Success);
                }

                SendMessage(arr);
                break;
            }
            case Util::Functions::CanEasyLoadWorkspace:
            {
                QByteArray arr = CreateMessage(Util::Functions::CanEasyStartSimulation, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::CanEasyStartSimulation:
            {
                if (m_CurrentFlashFile.IsUsb)
                {
                    QByteArray message;
                    QDataStream data(&message, QIODevice::WriteOnly);
                    data << DESTINATION + m_CurrentFlashFile.TargetDir;

                    QByteArray arr = CreateMessage(Util::Functions::UsbHidLoaderFlashFile, message, Util::ErrorID::Success);
                    SendMessage(arr);
                }
                else
                {
                    QByteArray arr = CreateMessage(Util::Functions::FHostSPStartFHost, "", Util::ErrorID::Success);
                    SendMessage(arr);
                }
                break;
            }
            case Util::Functions::CanEasyStopSimulation:
            {
                QByteArray arr = CreateMessage(Util::Functions::CanEasyCloseApplication, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::CanEasyCloseApplication:
            {
                QByteArray arr;
                QByteArray message;
                QDataStream data(&message, QIODevice::WriteOnly);


                if (m_FlashFiles.count() != 0)
                    m_CurrentFlashFile = m_FlashFiles.first();

                data << m_CurrentFlashFile.FlashFile;
                data << m_CurrentFlashFile.TargetDir;

                arr = CreateMessage(Util::Functions::MKSCreateSandBox, message, Util::ErrorID::Success);
                SendMessage(arr);
                if (!m_FlashFiles.isEmpty())
                    m_FlashFiles.removeFirst();

                break;
            }
            case Util::Functions::FHostSPStartFHost:
            {
                QString flashFileLocation = DESTINATION + m_CurrentFlashFile.TargetDir;
                QDir dir = QDir(flashFileLocation);
                QString FileName = "";
                QStringList files;

                if (m_CurrentFlashFile.IsUsb)
                {


                }
                else
                {
                    QString fileName = "*.prg";
                    files = dir.entryList(QStringList(fileName), QDir::Files);

                    if (m_CurrentFlashFile.FlashFile.contains("bootloader"))
                    {
                        for each (auto var in files)
                        {
                            if (var.contains("CB_") && !var.contains("IPL"))
                            {
                                FileName = var;
                            }
                        }
                    }
                    else
                    {
                        FileName = files.first();
                    }
                }



                QByteArray arr = CreateMessage(Util::Functions::FHostSPLoadFlashFile, (flashFileLocation + "/" + FileName).toUtf8(), Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::FHostSPLoadFlashFile:
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPStartFlash, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::FHostSPStartFlash:
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPGetState, "", Util::ErrorID::Success);
                ToogleCL30Fast(arr);
                break;
            }
            case Util::Functions::FHostSPGetState:
            {
                quint64 state = 0;
                QString status = "";
                QDataStream d(m.Message);
                d >> state;
                d >> status;


                if (Util::FHostSPState(state) == Util::FHostSPState::JOB_EXECUTING)
                {
                    QByteArray arr = CreateMessage(Util::Functions::FHostSPGetState, "", Util::ErrorID::Success);
                    SendMessage(arr);
                }
                else if (Util::FHostSPState(state) == Util::FHostSPState::JOB_EXECUTE_NOT_OK)
                {
                    QMessageBox msgBox;
                    msgBox.setText("Fehlermeldung von FHostSP ist : " + status);
                    msgBox.exec();

                    QByteArray arr = CreateMessage(Util::Functions::FHostSPAbortSequence, "", Util::ErrorID::Success);
                    SendMessage(arr);
                }
                else if (Util::FHostSPState(state) == Util::FHostSPState::JOB_EXECUTE_OK)
                {
                    QByteArray arr = CreateMessage(Util::Functions::FHostSPGetProgress, "", Util::ErrorID::Success);
                    SendMessage(arr);
                }
                break;
            }
            case Util::Functions::FHostSPGetProgress:
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPAbortSequence, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::FHostSPAbortSequence:
            {
                QByteArray arr = CreateMessage(Util::Functions::FHostSPCloseFHost, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::FHostSPCloseFHost:
            {
                QByteArray arr = CreateMessage(Util::Functions::CanEasyCloseApplication, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::MKSLogin:
            {
                QByteArray arr;
                QByteArray message;
                QDataStream data(&message, QIODevice::WriteOnly);


                if (m_FlashFiles.count() != 0)
                    m_CurrentFlashFile = m_FlashFiles.first();

                data << m_CurrentFlashFile.FlashFile;
                data << m_CurrentFlashFile.TargetDir;

                arr = CreateMessage(Util::Functions::MKSCreateSandBox, message, Util::ErrorID::Success);
                SendMessage(arr);
                if (!m_FlashFiles.isEmpty())
                    m_FlashFiles.removeFirst();
                break;
            }
            case Util::Functions::MKSCreateSandBox:
            {
                if (m_CurrentFlashFile.IsUsb)
                {
                    QByteArray message;
                    QDataStream data(&message, QIODevice::WriteOnly);
                    data << m_CurrentFlashFile.TargetDir;
                    QByteArray arr = CreateMessage(Util::Functions::FileUtilUnZip, message, Util::ErrorID::Success);
                    SendMessage(arr);
                }
                else
                {
                    QByteArray arr = CreateMessage(Util::Functions::CanEasyStartApplication, "", Util::ErrorID::Success);
                    SendMessage(arr);
                }
                break;
            }
            case Util::Functions::MKSDropSandbox:
            {
                QByteArray arr = CreateMessage(Util::Functions::MKSDropSandbox, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::PortalInfoShowDialog:
            {
                QString project = "";
                QString samplephase = "";
                QString release = "";
                bool bootloader = false;
                bool ac = false;
                bool gc = false;
                quint16 id = 0;
                int filecounter = 0;
                QString bootloaderFile;
                QString acFile = "";
                QString gcFile = "";
                QDataStream data(m.Message);
                data >> project;
                data >> samplephase;
                data >> release;
                data >> bootloader;
                data >> ac;
                data >> gc;
                data >> id;
                data >> filecounter;

                QString Path = project + "/" + samplephase + "/" + release;

                for (int i = 0; i < filecounter; i++)
                {
                    if (i == 0 && bootloader)
                        data >> bootloaderFile;
                    else if (i == 0 && bootloader == false && ac == true)
                        data >> acFile;
                    else if (i == 0 && bootloader == false && ac == true && gc == true)
                        data >> gcFile;
                    else if (i == 0 && bootloader == false && ac == false && gc == true)
                        data >> gcFile;
                    else if (i == 1 && bootloader == true && ac == true)
                        data >> acFile;
                    else if (i == 1 && bootloader == true && ac == false && gc == true)
                        data >> gcFile;
                    else if (i == 2 && ac == true && gc == true)
                        data >> gcFile;
                }
                if (!bootloaderFile.isEmpty())
                    m_FlashFiles.append(FlashInfo(bootloaderFile, Util::FlashType::Bootloader, Path + "/bootloader", false));
                if (!acFile.isEmpty())
                    m_FlashFiles.append(FlashInfo(acFile, Util::FlashType::AC, Path + "/ac", false));
                if (!gcFile.isEmpty())
                {
                    if (project.contains("HL"))
                    {
                        //Wir nutzen aktuell nur die USB Variante für die GC Files, deswegen suchen wir hier nach den HL
                        if (gcFile.endsWith("#flashfiles_FHOST") && gcFile.contains("HL"))
                            gcFile = gcFile.replace("#flashfiles_FHOST", "#flashfiles_USB");
                        m_FlashFiles.append(FlashInfo(gcFile, Util::FlashType::GC, Path + "/gc", true));
                    }
                    else if (project.contains("EL"))
                    {
                        m_FlashFiles.append(FlashInfo(gcFile, Util::FlashType::GC, Path + "/gc", false));
                    }

                }

                qDebug() << "Es wird das Projekt " << project << " mit der Samplehase " << samplephase << " und dem Release " << release << " geflasht.";
                qDebug() << "--------------------------------------------------------------------------------------------------------------------------------";
                if (bootloader)
                {
                    qDebug() << "Bootloader: " << bootloaderFile;
                    qDebug() << "--------------------------------------------------------------------------------------------------------------------------------";
                }
                if (ac)
                {
                    qDebug() << "AC:         " << acFile;
                    qDebug() << "--------------------------------------------------------------------------------------------------------------------------------";
                }
                if (gc)
                {
                    qDebug() << "GC:         " << gcFile;
                    qDebug() << "--------------------------------------------------------------------------------------------------------------------------------";
                }

                QByteArray arrMessage;
                QDataStream mksData(&arrMessage, QIODevice::WriteOnly);
                mksData << QString("C:\\Temp\\IntegrityClient10.8\\bin\\");
                mksData << QString("uidw5301");
                mksData << QString("Windows2001");

                QByteArray arr = CreateMessage(Util::Functions::MKSLogin, arrMessage, Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::PortalInfoCloseDialog:
            {
                //QByteArray arr = CreateMessage(Util::Functions::FHostSPGetState, "", Util::ErrorID::Success);
                //SendMessage(arr);
                //break;
            }
            case Util::Functions::FileUtilUnZip:
            {
                QByteArray arr = CreateMessage(Util::Functions::CanEasyStartApplication, "", Util::ErrorID::Success);
                SendMessage(arr);
                break;
            }
            case Util::Functions::FileUtilDelete:
            {
                break;
            }
            case Util::Functions::UsbHidLoaderFlashFile:
            {
                QByteArray arr = CreateMessage(Util::Functions::CanEasyCloseApplication, "", Util::ErrorID::Success);
                ToogleCL30Fast(arr);
                break;
            }
            default:
                break;
            }
        }
    }
}


QDataStream &operator <<(QDataStream &out, const RW::CORE::Message &dataStruct)
{
    out.startTransaction();
    out << (quint16)dataStruct.MessageType;
    out << dataStruct.MessageSize;
    out.writeRawData(dataStruct.Message, dataStruct.MessageSize);
    out << (quint16)dataStruct.Error;
    out.commitTransaction();
    return out;
}

QDataStream &operator >>(QDataStream &in, RW::CORE::Message &dataStruct)
{
    quint16 messageType = 0;
    quint16 id = 0;
    in >> messageType;
    in >> dataStruct.MessageSize;
    dataStruct.Message.resize(dataStruct.MessageSize);
    in.readRawData(dataStruct.Message.data(), dataStruct.MessageSize);
	in >> id;

    dataStruct.MessageType = static_cast<RW::CORE::Util::Functions>(messageType);
	dataStruct.Error = static_cast<RW::CORE::Util::ErrorID>(id);
    return in;
}

QString GetMKSLink(QString Destination, QString MksLink)
{
	QRegExp reg("#b=\\d{1,1}.\\d{1,5}#");
	int i = reg.indexIn(MksLink);
	int ii = reg.matchedLength();
	MksLink = MksLink.replace(i + ii - 1, MksLink.count() - (i + ii - 1), "");

	QString left = MksLink.replace("#b=", "/");
	left = left.replace("#/id/", "");

	return Destination + left;
}