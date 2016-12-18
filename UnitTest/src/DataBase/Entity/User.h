#pragma once
#include "Entity.h"

namespace RW{
	namespace SQL{

		class User :
			public Entity
		{
			Q_OBJECT
			Q_PROPERTY(quint64 Ingredient MEMBER m_IngredientID READ IngredientID WRITE SetIngredientID NOTIFY IngredientIDChanged)
			Q_CLASSINFO("Version", "0.0.1")

		private:
			quint64 m_IngredientID;
		public:
			User(Entity *Parent = nullptr);
			~User();


			quint64 IngredientID(){ return m_IngredientID; }
			void SetIngredientID(quint64 ReceptID){ m_IngredientID = ReceptID; emit IngredientIDChanged(); }


		signals:
			void IngredientIDChanged();

		};
	}
}