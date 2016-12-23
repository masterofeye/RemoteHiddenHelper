#pragma once
#include "qobject.h"
namespace RW{
	namespace CORE{

		class CommunicationManager :
			public QObject
		{
			Q_OBJECT
		public:
			CommunicationManager(QObject *Parent = nullptr);
			~CommunicationManager();
		};
	}
}
