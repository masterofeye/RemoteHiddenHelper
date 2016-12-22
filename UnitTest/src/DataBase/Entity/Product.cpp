#include "Product.h"
#include "Product_p.h"

namespace RW{
	namespace SQL{


		ProductPrivate::ProductPrivate(Product* Parent) :
			QObject(Parent),
			q_ptr(Parent),
			m_ProductName(""),
			m_Part(""),
			m_Recept()
		{
		}

		ProductPrivate::~ProductPrivate()
		{
		}


		Product::Product(Entity *Parent) : Entity(Parent),
			d_ptr(new ProductPrivate(this))
		{
		}


		Product::~Product()
		{
			delete d_ptr;
		}

		QString Product::ProductName()
		{
			Q_D(Product);
			return d->m_ProductName; 
		}
		void Product::SetProductName(QString Product)
		{
			Q_D(Product);
			d->m_ProductName = Product; 
			emit ProductNameChanged();
		}

		QString Product::Part()
		{
			Q_D(Product);
			return d->m_Part; 
		}

		void Product::SetPart(QString Step)
		{
			Q_D(Product);
			d->m_Part = Step; 
			emit PartChanged();
		
		}

		Recept& Product::Recept()
		{
			Q_D(Product);
			return d->m_Recept; 
		}

		void Product::SetRecept(RW::SQL::Recept &ReceptID)
		{
			Q_D(Product);
			d->m_Recept = ReceptID; 
			emit ReceptChanged(); 
		}
	}
}
