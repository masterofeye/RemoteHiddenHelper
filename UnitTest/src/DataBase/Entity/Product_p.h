#pragma once
#include <qobject.h>
#include "Recept.h"

namespace RW{
	namespace SQL{

		class Product;
		class ProductPrivate : public QObject
		{
			Q_OBJECT
				Q_DISABLE_COPY(ProductPrivate)
				Q_DECLARE_PUBLIC(Product)
		private:
			Product * const q_ptr;
		public:
			QString m_ProductName;
			QString m_Part;
			Recept m_Recept;
		public:
			ProductPrivate(Product *Parent);
			~ProductPrivate();
		};
	}
}