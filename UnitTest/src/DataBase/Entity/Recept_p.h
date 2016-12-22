#pragma once
#include <qobject.h>
#include "Instruction.h"

namespace RW{
	namespace SQL{

		class Recept;

		class ReceptPrivate : public QObject
		{
				Q_OBJECT
				Q_DISABLE_COPY(ReceptPrivate)
				Q_DECLARE_PUBLIC(Recept)
		private:
			Recept * const q_ptr;
		public: 
			Instruction m_InstructionID;
			quint16 m_OrderNumber;
			QString m_ReceptName;
		public:
			ReceptPrivate(Recept *Parent);
			~ReceptPrivate();

			//// copy constructor
			//Recept(const Recept& rhs){
			//	this->m_IngredientID = rhs.m_IngredientID;
			//	this->m_OrderNumber = rhs.m_OrderNumber;
			//	this->m_ReceptName = rhs.m_ReceptName;
			//}
			//// move constructor
			//Recept(Recept&& rhs){
			//	this->m_IngredientID = rhs.m_IngredientID;
			//	this->m_OrderNumber = rhs.m_OrderNumber;
			//	this->m_ReceptName = rhs.m_ReceptName;
			//}
			//// copy Recept operator
			//Recept& operator=(const Recept& rhs) {
			//	this->m_IngredientID = rhs.m_IngredientID;
			//	this->m_OrderNumber = rhs.m_OrderNumber;
			//	this->m_ReceptName = rhs.m_ReceptName;
			//	return *this;
			//}
			//// move assignment operator
			//Recept& operator=(Recept&& rhs) {
			//	this->m_IngredientID = rhs.m_IngredientID;
			//	this->m_OrderNumber = rhs.m_OrderNumber;
			//	this->m_ReceptName = rhs.m_ReceptName;
			//	return *this;
			//}

		signals:
		};
	}
}