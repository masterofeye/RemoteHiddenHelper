#ifndef REMOTEHIDDENHELPER_H
#define REMOTEHIDDENHELPER_H

#include <QSystemtrayicon>
#include "RemoteDataConnectLibrary.h"

namespace RW{
	namespace CORE{
		class ProcessManager;
		class RemoteHiddenHelper : public QSystemTrayIcon
		{
			Q_OBJECT

		private:
			ProcessManager* m_ProcessManager;
            QMenu* m_TrayMenu;
            std::shared_ptr<spdlog::logger> m_Logger;
		public:
			RemoteHiddenHelper(QObject *parent = 0);
			~RemoteHiddenHelper();

            
        private:
            void CreateContextMenu();
        private slots:
            void OnPermanetLogin(bool Checked);
            void OnResetCheckedPermanetLogin();
            void OnCheckPermanentCheckBox(bool Checked);
		};
	}
}


#endif // REMOTEHIDDENHELPER_H
