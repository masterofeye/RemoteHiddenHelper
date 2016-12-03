#include "remotehiddenhelper.h"
#include <qdebug.h>
#include <qfile.h>

#include "ProcessManager.h"

namespace RW{
	namespace CORE{
		RemoteHiddenHelper::RemoteHiddenHelper(QObject *parent)
			: QSystemTrayIcon(parent),
			m_ProcessManager(new ProcessManager(this))
		{
			setIcon(QIcon(":/RemoteHiddenHelper/helper.png"));

		}

		RemoteHiddenHelper::~RemoteHiddenHelper()
		{
		}
	}
}