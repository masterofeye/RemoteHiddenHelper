#pragma once
#include "Entity.h"
#include "SQLGlobal.h"

namespace RW{
	namespace SQL{

		class ElementTypePrivate;
		class ElementType :
			public Entity
		{
			Q_OBJECT
			Q_CLASSINFO("Version", "0.0.1")
		private:
			ElementTypePrivate* d_ptr;
			Q_DECLARE_PRIVATE(ElementType);
		public:
			ElementType(Entity *Parent = nullptr);
			~ElementType();

			TypeOfElement Type();
			void SetType(TypeOfElement Type);

			ElementType(const ElementType& other);
			ElementType& ElementType::operator=(ElementType& other);

			ElementType(ElementType&& other);
			ElementType& ElementType::operator=(ElementType&& other);

		};
	}
}