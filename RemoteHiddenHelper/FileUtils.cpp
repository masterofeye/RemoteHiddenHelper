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

		void FileUtils::OnProcessMessage(COM::Message Msg)
        {
			switch (Msg.MessageID())
            {
			case COM::MessageDescription::EX_FileUtilUnZip:{
				QString file;

				file = Msg.ParameterList()[0].toString();
                // \!todo Magic Number .. der Pfad wird mehrfach verwendet
                Unzip(QDir("C:\\Temp\\" + file));
            }
                break;
			case COM::MessageDescription::EX_FileUtilDelete:
            {
                QString dir;
				dir = Msg.ParameterList()[0].toString();
                Delete(QDir(dir));
            }
                break;
            default:
                break;
            }
        }

        void FileUtils::Unzip(QDir &Dir)
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FileUtilUnZip);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            QStringList files = Dir.entryList(QStringList(SEARCHPATTERN), QDir::Files);
            if (files.count() == 0)
            {
                msg.SetSuccess(false);
                msg.SetResult("No files avaiable .");
                emit NewMessage(msg);
                return;
            }

            if(!QFile(SEVENZIP).exists())
            {
                msg.SetSuccess(false);
                msg.SetResult("Sevenzip isn't avaible.");
                emit NewMessage(msg);
                return;
            }

            QProcess proc;
            QStringList arguments;
            arguments << COMMAND << SEARCHPATTERN << OVERWRITE;
            proc.setWorkingDirectory(Dir.absolutePath());
            proc.start(SEVENZIP, arguments);
            if (!proc.waitForFinished(30000))
            {
                msg.SetSuccess(false);
                msg.SetResult("Timeout for flash procedure");
                emit NewMessage(msg);
            }

            msg.SetSuccess(true);
            emit NewMessage(msg);
        }
        
        void FileUtils::Delete(QDir &Directory)
        {
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_FileUtilDelete);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            //Überprüfen ob das Directory überhaupt existiert
            if (!Directory.exists())
            {
                msg.SetSuccess(false);
                msg.SetResult("Directory doesn't exist: ." + Directory.absolutePath());
                emit NewMessage(msg);
            }

            //Nun den Ordner entfernen
            if (!Directory.removeRecursively())
            {
                msg.SetSuccess(false);
                msg.SetResult("Sevenzip isn't avaible.");
                emit NewMessage(msg);
            }
            msg.SetSuccess(true);
            emit NewMessage(msg);
        }
    }
}