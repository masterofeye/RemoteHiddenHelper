#pragma once
#include "Entity.h"

namespace RW{
	namespace SQL{
		class ElementType;

		class ElementConfiguration :
			public Entity
		{
			Q_OBJECT

			Q_PROPERTY(ElementType Type MEMBER m_Type READ Type WRITE SetType NOTIFY TypeChanged)
			Q_PROPERTY(QString DisplayName MEMBER m_DisplayName READ DisplayName WRITE SetDisplayName NOTIFY DisplayNameChanged)
			Q_PROPERTY(QString Name MEMBER m_Name READ Name WRITE SetName NOTIFY NameChanged)
			Q_PROPERTY(QString Group MEMBER m_Group READ Group WRITE SetGroup NOTIFY GroupChanged)
			Q_PROPERTY(QString Function MEMBER m_Function READ Function WRITE SetFunction NOTIFY FunctionChanged)

			Q_CLASSINFO("Version", "0.0.1")
		private:
			ElementType* m_Type;
			QString m_DisplayName;
			QString m_Name;
			QString m_Group;
			QString m_Function;
		
		public:
			ElementConfiguration(Entity *Parent = nullptr);
			~ElementConfiguration();

			ElementConfiguration& operator=(const ElementConfiguration &obj);

			ElementType& Type(){ return *m_Type; }
			void SetType(ElementType &Type);

			QString DisplayName(){ return m_DisplayName; }
			void SetDisplayName(QString DisplayName){ m_DisplayName = DisplayName; emit DisplayNameChanged(); }

			QString Name(){ return m_Name;}
			void SetName(QString Name){ m_Name = Name; emit NameChanged(); }

			QString Group(){ return m_Group; }
			void SetGroup(QString Group){ m_Group = Group; emit GroupChanged(); }

			QString Function(){ return m_Function; }
			void SetFunction(QString Function){ m_Function = Function; emit FunctionChanged(); }
			

		signals:
			void TypeChanged();
			void DisplayNameChanged();
			void NameChanged();
			void GroupChanged();
			void FunctionChanged();
		};
	}
}
