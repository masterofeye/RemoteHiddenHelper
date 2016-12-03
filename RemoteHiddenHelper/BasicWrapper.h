#pragma once
#include "qobject.h"
#include "Constants.h"

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
			virtual void OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report) = 0;

		signals:
			void NewMessage(Util::Functions Func, Util::ErrorID MessageType, QByteArray Message);
		};
	}
}
