#pragma once
#include <qobject.h>
#include "ElementType.h"

namespace RW{
	namespace SQL{

		class ElementConfiguration;
		class ElementConfigurationPrivate : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY(ElementConfigurationPrivate)
			Q_DECLARE_PUBLIC(ElementConfiguration)
		private:
			ElementConfiguration * const q_ptr;

		public:
			ElementType m_Type;
			QString m_DisplayName;
			QString m_Name;
			QString m_Group;
			QString m_Function;
		public:
			ElementConfigurationPrivate(ElementConfiguration* QPointer);
			~ElementConfigurationPrivate();
		};


	}
}