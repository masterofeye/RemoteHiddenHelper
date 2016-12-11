#pragma once
#include "Entity.h"

namespace RW{
	namespace SQL{

		class Recept :
			public Entity
		{
			Q_OBJECT
			Q_PROPERTY(quint64 Ingredient MEMBER m_IngredientID READ IngredientID WRITE SetIngredientID NOTIFY IngredientIDChanged)
			Q_PROPERTY(quint16 OrderNumber MEMBER m_OrderNumber READ OrderNumber WRITE SetOrderNumber NOTIFY OrderNumberChanged)
			Q_PROPERTY(QString ReceptName MEMBER m_ReceptName READ ReceptName WRITE SetReceptName NOTIFY ReceptNameChanged)
			Q_CLASSINFO("Version", "0.0.1")

		private:
			quint64 m_IngredientID;
			quint16 m_OrderNumber;
			QString m_ReceptName;
		public:
			Recept(Entity *Parent = nullptr);
			~Recept();

			// copy constructor
			Recept(const Recept& rhs){
				this->m_IngredientID = rhs.m_IngredientID;
				this->m_OrderNumber = rhs.m_OrderNumber;
				this->m_ReceptName = rhs.m_ReceptName;
			}
			// move constructor
			Recept(Recept&& rhs){
				this->m_IngredientID = rhs.m_IngredientID;
				this->m_OrderNumber = rhs.m_OrderNumber;
				this->m_ReceptName = rhs.m_ReceptName;
			}
			// copy Recept operator
			Recept& operator=(const Recept& rhs) { 
				this->m_IngredientID = rhs.m_IngredientID;  
				this->m_OrderNumber = rhs.m_OrderNumber;
				this->m_ReceptName = rhs.m_ReceptName;
				return *this; }
			// move assignment operator
			Recept& operator=(Recept&& rhs) { 
				this->m_IngredientID = rhs.m_IngredientID; 
				this->m_OrderNumber = rhs.m_OrderNumber;
				this->m_ReceptName = rhs.m_ReceptName;
				return *this; }


			quint64 IngredientID(){ return m_IngredientID; }
			void SetIngredientID(quint64 ReceptID){ m_IngredientID = ReceptID; emit IngredientIDChanged(); }

			quint16 OrderNumber(){ return m_OrderNumber; }
			void SetOrderNumber(quint16 Order){ m_OrderNumber = Order; emit OrderNumberChanged(); }

			QString ReceptName(){ return m_ReceptName; }
			void SetReceptName(QString Order){ m_ReceptName = Order; emit ReceptNameChanged(); }

		signals:
			void OrderNumberChanged();
			void IngredientIDChanged();
			void ReceptNameChanged();
		};
	}
}