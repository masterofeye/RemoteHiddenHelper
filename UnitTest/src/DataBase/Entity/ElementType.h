#pragma once
#include "Entity.h"

namespace RW{
	namespace SQL{

		class ElementType :
			public Entity
		{
			Q_OBJECT
				Q_PROPERTY(TypeOFElement Type MEMBER m_Type READ Type WRITE SetType NOTIFY TypeChanged)
			Q_CLASSINFO("Version", "0.0.1")
		public: 
			enum class TypeOFElement
			{
				USB,
				IO,
				RELAY,
				SOUND,
				INVALID
			};

		private:
			TypeOFElement m_Type;
		public:
			ElementType(Entity *Parent = nullptr);
			~ElementType();
			ElementType& operator=(const ElementType &obj);

			TypeOFElement Type(){ return m_Type; }
			void SetType(TypeOFElement Type){ m_Type = Type; emit TypeChanged(); }

		signals:
			void TypeChanged();
		};
	}
}