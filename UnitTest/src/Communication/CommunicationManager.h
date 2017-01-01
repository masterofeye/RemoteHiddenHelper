#pragma once
#include "qobject.h"
#include "qvariant.h"

namespace RW{
	namespace CORE{

		class CommunicationManager :
			public QObject
		{
			Q_OBJECT
		public:
			CommunicationManager(QObject *Parent = nullptr);
			~CommunicationManager();

		public slots: 
			void OnProcessMessage(QVariant Data);
		};
	}
}
