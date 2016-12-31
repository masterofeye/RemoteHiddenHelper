#pragma once
#include "Entity.h"


namespace RW{
	namespace SQL{
		class ElementType;
		class ElementConfigurationPrivate;

		/*
		@brief Enititätsklasse, die die Konfiguration einer funktionieralität kapselt. Des kann z.b. die Kl30 sein oder aber 
		auch der FHostSP start. 
		*/
		class ElementConfiguration :
			public Entity
		{
			Q_OBJECT
			Q_PROPERTY(ElementType Type NOTIFY TypeChanged)
			Q_PROPERTY(QString DisplayName  READ DisplayName WRITE SetDisplayName NOTIFY DisplayNameChanged)
			Q_PROPERTY(QString Name READ Name WRITE SetName NOTIFY NameChanged)
			Q_PROPERTY(QString groupName READ GroupName WRITE SetGroupName NOTIFY GroupNameChanged)
			Q_PROPERTY(QString Function READ Function WRITE SetFunction NOTIFY FunctionChanged)
			Q_CLASSINFO("Version", "0.0.1")
		private:
			ElementConfigurationPrivate* d_ptr;
			Q_DECLARE_PRIVATE(ElementConfiguration);

		public:
			explicit ElementConfiguration(Entity *Parent = nullptr);
			~ElementConfiguration();

			/*
			@brief Copy Konstruktor
			@param [in]  Other
			*/
			ElementConfiguration(const ElementConfiguration& other);

			/*
			@brief Copy Operator
			@param [in] Other
			@return ElementConfiguration
			*/
			ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration& other);

			/*
			@brief Move Konstruktor
			@param [in] Other
			*/
			ElementConfiguration(ElementConfiguration&& other);

			/*
			@brief Move Operator 
			@param Other 
			@return ElementConfiguration
			*/
			ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration&& other);

			/*
			@brief Gibt den Type des Konfigurationselementes zurück
			*/
			ElementType& Type();

			/*
			@brief Setzt den Type des Konfigurationselement.
			@param [in] ElementType 
			*/
			void SetType(ElementType &Type);

			/*
			@brief Entspricht dem anzeigten Namen in der RemoteApp
			@return QStríng Der Name der Anzeigt wird für die Funktionalität in der RemoteApp
			*/
			QString DisplayName();

			/*
			@brief Setzt den Anzeigename für die RemoteApp
			@param [in] DisplayName 
			*/
			void SetDisplayName(QString DisplayName);

			/*
			@brief Name der Funktionalität. Kann intern genutzt werden um bestimmte Ereignisse zu triggern.
			@return QString Gibt den Namen der Funktionaliät zurück. 
			*/
			QString Name();

			/*
			@brief Setzt den Namen der Funktionalität.
			@param [in] Name Name der Funktionalität.
			*/
			void SetName(QString Name);

			/*
			@brief Name der Gruppe unter der die Funktionalität gelistet werden soll.
			@oaram GroupName Name der Gruppe
			*/
			QString GroupName();

			/*
			@brief Setzt den Gruppennamen in der die Funktionalität in der RemoteAPP gelistet werden soll.
			@param [in] GroupName Name der Gruppe.
			*/
			void SetGroupName(QString GroupName);

			/*
			@brief Funktion die hinter der Funktionalität steckt
			@return QString
			*/
			QString Function();

			/*
			@brief Setzt die Funkktion die hinter der Funtinionalität steckt
			@param Function 
			*/
			void SetFunction(QString Function);

		signals:
			/*
			@brief Signalisiert wenn sich der Type geändert hat.
			*/
			void TypeChanged();

			/*
			@brief Wird ausgelöst wenn sich der Displayname geändert hat. 
			*/
			void DisplayNameChanged();

			/*
			@brief Wird ausgelöst wenn sich der Name geändert hat. 
			*/
			void NameChanged();

			/*
			@brief Wird ausgelöst wenn sich der Gruppenname geändert hat.
			*/
			void GroupNameChanged();

			/*
			@brief Wird ausgelöst wenn sich die Funktion geändert hat
			*/
			void FunctionChanged();
		};
	}
}
