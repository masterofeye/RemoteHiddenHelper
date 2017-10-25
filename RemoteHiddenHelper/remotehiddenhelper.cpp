#include "remotehiddenhelper.h"
#include "ProcessManager.h"
#include <qdebug.h>
#include <qfile.h>
#include <qmenu.h>



namespace RW{
    namespace CORE{
        RemoteHiddenHelper::RemoteHiddenHelper(QObject *parent)
            : QSystemTrayIcon(parent),
            m_TrayMenu(nullptr)
        {
            setIcon(QIcon(":/RemoteHiddenHelper/helper.png"));
            m_Logger = spdlog::get("file_logger");
            if (m_Logger == nullptr)
            {
                m_Logger = spdlog::create<spdlog::sinks::MySqlSink>("file_logger");
            }
            m_Logger->set_pattern("[%H:%M:%S:%f] [%g] [%l] [thread %t] %v ");
#ifdef REMOTESERVICE_DEBUG
            m_Logger->set_level(spdlog::level::debug);
#else
            m_Logger->set_level(spdlog::level::info);
#endif 
            m_Logger->set_type(4);

            m_ProcessManager = new ProcessManager(this);
            CreateContextMenu();
            connect(m_ProcessManager, &ProcessManager::ResetPermanentCheckBox, this, &RemoteHiddenHelper::OnResetCheckedPermanetLogin);
            connect(m_ProcessManager, &ProcessManager::CheckPermanentCheckBox, this, &RemoteHiddenHelper::OnCheckPermanentCheckBox);

        }

        RemoteHiddenHelper::~RemoteHiddenHelper()
        {
            delete m_TrayMenu;
        }

        void RemoteHiddenHelper::CreateContextMenu()
        {
            m_TrayMenu = new QMenu();

            QAction* action = new QAction();
            action->setCheckable(true);
            action->setText("Permanent Login");

            connect(action, &QAction::triggered, this, &RemoteHiddenHelper::OnPermanetLogin);

            m_TrayMenu->addAction(action);

            this->setContextMenu(m_TrayMenu);
        }

        void RemoteHiddenHelper::OnPermanetLogin(bool Checked)
        {
            COM::Message m;
            m.SetMessageID(COM::MessageDescription::EX_PermanentLogin );
            m.SetIsExternal(true);
            m.setIdentifier(m.GenUUID(COM::TypeofServer::RemoteHiddenHelper).toString());
            QList<QVariant> list;
            list.append(Checked);

            m.SetParameterList(list);
            emit m_ProcessManager->NewMessage(m);
        }

        void RemoteHiddenHelper::OnResetCheckedPermanetLogin()
        {
            QList<QAction*> list =m_TrayMenu->actions();
            for each (auto var in list)
            {
                if (var->text() == "Permanent Login")
                {
                    var->setChecked(false);
                }
            }  
        }

        void RemoteHiddenHelper::OnCheckPermanentCheckBox(bool Checked)
        {
            QList<QAction*> list = m_TrayMenu->actions();
            for each (auto var in list)
            {
                if (var->text() == "Permanent Login")
                {
                    var->setChecked(Checked);
                }
            }
        }
	}
}