#include "FileUtils.h"
#include <qdatastream.h>
#include <qfile.h>
#include <qdir.h>
#include <qprocess.h>

namespace RW
{
    namespace CORE
    {
        const QString SEVENZIP = "C:\\Program Files\\7-Zip\\7z.exe";
        const QString COMMAND = "x";
        const QString SEARCHPATTERN = "*.7z";
        const QString OVERWRITE = "-aoa";


        FileUtils::FileUtils(QObject *Parent) : BasicWrapper(Parent)
        {
        }

        FileUtils::~FileUtils()
        {
        }

        void FileUtils::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
        {
            if (Type == Util::MessageReceiver::FileUtil)
            {
                switch (Func)
                {
                case RW::CORE::Util::Functions::FileUtilUnZip:{
                    QString file;
                    QDataStream data(Report);
                    data >> file;
                    // \!todo Magic Number .. der Pfad wird mehrfach verwendet
                    Unzip(QDir("C:\\Temp\\" + file));
                }
                    break;
                case RW::CORE::Util::Functions::FileUtilDelete:
                {
                    QString dir;
                    QDataStream data(Report);
                    data >> dir;
                    Delete(QDir(dir));
                }
                    break;
                default:
                    break;
                }
            }
        }

        void FileUtils::Unzip(QDir &Dir)
        {
            QStringList files = Dir.entryList(QStringList(SEARCHPATTERN), QDir::Files);
            if (files.count() == 0)
            {
                emit NewMessage(Util::Functions::FileUtilUnZip, Util::ErrorID::ErrorFileUtilMissingZipFile, "");
                return;
            }

            if(!QFile(SEVENZIP).exists())
            {
                emit NewMessage(Util::Functions::FileUtilUnZip, Util::ErrorID::ErrorFileUtilNoSevenZip, "");
                return;
            }

            QProcess proc;
            QStringList arguments;
            arguments << COMMAND << SEARCHPATTERN << OVERWRITE;
            proc.setWorkingDirectory(Dir.absolutePath());
            proc.start(SEVENZIP, arguments);
            if(!proc.waitForFinished(30000))
                emit NewMessage(Util::Functions::FileUtilUnZip, Util::ErrorID::ErrorFileUtilFailed, "");
            emit NewMessage(Util::Functions::FileUtilUnZip, Util::ErrorID::Success, "");
        }
        
        void FileUtils::Delete(QDir &Directory)
        {
            //Überprüfen ob das Directory überhaupt existiert
            if (!Directory.exists())
            {
                emit NewMessage(Util::Functions::FileUtilDelete, Util::ErrorID::ErrorFileUtilDirectoryDontExists, "");
            }

            //Nun den Ordner entfernen
            if (!Directory.removeRecursively())
            {
                emit NewMessage(Util::Functions::FileUtilDelete, Util::ErrorID::ErrorFileUtilDeleteFailed, "");
            }

            emit NewMessage(Util::Functions::FileUtilDelete, Util::ErrorID::Success, "");
        }
    }
}