#ifndef REMOTEHIDDENHELPER_H
#define REMOTEHIDDENHELPER_H

#include <QSystemtrayicon>


namespace RW{
	namespace CORE{
		class ProcessManager;
		class RemoteHiddenHelper : public QSystemTrayIcon
		{
			Q_OBJECT

		private:
			ProcessManager* m_ProcessManager;
		public:
			RemoteHiddenHelper(QObject *parent = 0);
			~RemoteHiddenHelper();

		};
	}
}


#endif // REMOTEHIDDENHELPER_H
