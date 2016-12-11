#include "Recept.h"

namespace RW{
	namespace SQL{

		Recept::Recept(Entity *Parent) : Entity(Parent),
			m_OrderNumber(0),
			m_IngredientID(0)
		{
		}


		Recept::~Recept()
		{
		}
	}
}