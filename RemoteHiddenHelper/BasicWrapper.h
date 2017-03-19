#pragma once
#include "qobject.h"
#include "Constants.h"
#include "RemoteCommunicationLibrary.h"

namespace RW{
	namespace CORE{

		class BasicWrapper :
			public QObject
		{
			Q_OBJECT
		public:
			BasicWrapper(QObject* Parent = nullptr) : QObject(Parent)
			{}
			virtual ~BasicWrapper(){}
		public slots:
			virtual void OnProcessMessage(RW::COM::Message Msg) = 0;

		signals:
			void NewMessage(COM::Message Msg);
		};
	}
}
