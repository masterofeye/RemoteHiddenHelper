#pragma once
#include "Entity.h"


namespace RW{
	namespace SQL{
		class ElementType;
		class ElementConfigurationPrivate;

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


			ElementConfiguration(const ElementConfiguration& other);
			ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration& other);

			ElementConfiguration(ElementConfiguration&& other);
			ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration&& other);

			ElementType& Type();
			void SetType(ElementType &Type);

			QString DisplayName();
			void SetDisplayName(QString DisplayName);

			QString Name();
			void SetName(QString Name);

			QString GroupName();
			void SetGroupName(QString GroupName);

			QString Function();
			void SetFunction(QString Function);

		signals:
			void TypeChanged();
			void DisplayNameChanged();
			void NameChanged();
			void GroupNameChanged();
			void FunctionChanged();
		};
	}
}
