#pragma once
#include <qobject.h>
#include "SQLGlobal.h"

namespace RW{
	namespace SQL{

		class ElementType;
		class ElementTypePrivate : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY(ElementTypePrivate)
			Q_DECLARE_PUBLIC(ElementType)
			//Q_PROPERTY(TypeOFElement Type MEMBER m_Type READ Type WRITE SetType NOTIFY TypeChanged)
		private:
			ElementType * const q_ptr;
		public:
			TypeOfElement m_Type;
		public:
			ElementTypePrivate(ElementType *Parent);
			~ElementTypePrivate();
		signals:
			void TypeChanged();
		};
	}
}