#pragma once
#include <QtCore>
#include "Constants.h"

namespace RW{
	namespace CORE{
		class CommunicationServer;
        class ErrorHandler;

		class CommunicationManager :
			public QObject
		{
			Q_OBJECT
		private: 
			CommunicationServer* m_Server;
            ErrorHandler* m_ErrorHandler;
        private:
			QByteArray CreateMessage(Util::Functions Func, QByteArray Message, Util::ErrorID Id);
        private slots:
            void OnProcessMessage(Util::Functions MessageType, QByteArray Message);
        public slots:

		void OnProcessMessageAnswer(Util::Functions Func, Util::ErrorID Id, QByteArray Message);
		public:
            CommunicationManager(ErrorHandler* ErrorHandler, QObject* Parent = nullptr);
			~CommunicationManager();

		signals: 
			void NewMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report);
		};
	}
}
