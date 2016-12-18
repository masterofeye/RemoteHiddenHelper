#pragma once
#include "qobject.h"
namespace RW{
	namespace CORE{

		class CommuncationManager :
			public QObject
		{
			Q_OBJECT
		public:
			CommuncationManager(QObject *Parent = nullptr);
			~CommuncationManager();
		};
	}
}
