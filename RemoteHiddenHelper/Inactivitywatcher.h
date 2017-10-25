#ifndef INTACTIVITYWATCHER_H
#define INTACTIVITYWATCHER_H
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "spdlog\spdlog.h"
#include "BasicWrapper.h"

namespace RW{
    enum class WorkstationKind;
	namespace CORE{

        /*!
        @Autor Ivo Kunadt
        @brief Die Klasse stellt Funktionalitäten bereit, um den User aus dem aktuellen Rechner auszuloggen. 
        @details Dabei ist es möglich den User direkt (LogOutUser) auszuloggen oder erst nach einem bestimmten Timeout (LogOutUser).
        Beide Funktionen sollten nur durch das Messagesystem genutzt werden. 
        Dabei werden folgende Messages unterstützt.
        - EX_StartInactivityTimer  -> Logout per Timer starten
        - EX_StopInactivityTimer   -> Stoppt den Logoutmechanismus
        - EX_LogoutImmediately     -> Führt sofort zu einem Logout

        @see InactivityWatcher#LogOutUser
        @see InactivityWatcher#LogOutUserByTimer
        */
		class InactivityWatcher : public BasicWrapper
		{
			Q_OBJECT
		private:
			std::shared_ptr<spdlog::logger> m_logger;
			QTimer *m_TimerLogout;
			long long m_Timeout;
            QTime m_LogoutTimeStart;
            QTime m_LogoutTimeEnd;
			QString m_UserName;
            bool m_IsPermanent;
            WorkstationKind m_WorkstationType;
            QTimer *m_PermamentTimout;
            QDateTime m_MaxPermanentLoginTime;
		public:
			explicit InactivityWatcher(QObject *parent = 0);
		private: 
            /**
            @Autor Ivo Kunadt
            @brief Startet den Logoutmechanismus.
            */
            void StartInactivityObservation();

            /*!
            @Autor Ivo Kunadt
            @brief Stoppt den Logoutmechanismus.
            */
            void StopInactivityObservation();

            /*!
            @Autor Ivo Kunadt
            @brief SessionNumber Liefert die aktuelle SessionID für den angemeldeten Benutzer zurück.
            @todo sollte nicht in dieser Klassen erfolgen, sondern in einer Helperklasse.
            */
			bool QueryActiveSession(quint64 &SessionNumber, QString Username);

            /*!
            @Autor Ivo Kunadt
            @brief Liefert die Zeit (in Millisekunden) zurück, die der angemeldete Benutzer inaktiv ist. 
            @return Zeit, die der Nutzer inaktiv ist. 
            */
			uint GetLastInputTime();
        signals:
            /*!
            @Autor Ivo Kunadt
            @brief SessionNumber Signal wird ermittet sobald der User ausgeloggt ist. 
            */
            void LogOff(quint64 SessionNumber);
		private slots:
            /*!
            @Autor Ivo Kunadt
            @brief Logt den Nutzer, der verbunden ist mit der übergebenen SessionID aus dem Rechner aus. 
            @param SessionNumber SessionID des angemeldeten Benutzers. 
            */
            void OnLogOff(quint64 SessionNumber);

            /*!
            @Autor Ivo Kunadt
            @brief Diese Funktion kann dazu genutzt werden, den aktuell angemeldeten Benutzer aus dem Rechner auszuloggen.
            Sollte aber nur mit dem Messagesystem benutzt werden. 
            */
			void LogOutUser();

            /*!
            @Autor Ivo Kunadt
            @brief Der angemeldete Nutzer wird aufgrund eines definierten Timers ausgeloggt. 
            */
            void LogOutUserByTimer();

            /*!
            @Autor Ivo Kunadt
            @brief Beendet den permanent Loginmodus.
            */
            void OnPermanetLoginEnd();

		public slots:
            /*!
            @Autor Ivo Kunadt
            @brief Verarbeitet die ankommen Messages. Die Message werden durch einen Filter sortiert.
            @param COM::Message Message Objekt mit den benötigten Informationen (Parameter, Status usw.).
            */
            void OnProcessMessage(COM::Message msg);
		};
	}
}
#endif // INTACTIVITYWATCHER_H
