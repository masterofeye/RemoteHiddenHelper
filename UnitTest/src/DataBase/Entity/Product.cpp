#include "Product.h"

namespace RW{
	namespace SQL{
		Product::Product(Entity *Parent) : Entity(Parent),
			m_ProductName(""),
			m_Part(""),
			m_Recept(this)
		{
		}


		Product::~Product()
		{
		}
	}
}
