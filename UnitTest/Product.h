#pragma once

#include "Entity.h"
#include "Recept.h"
namespace RW{
	namespace SQL{
		class Product :
			public Entity
		{
			Q_OBJECT
			Q_PROPERTY(QString ProductName MEMBER m_ProductName READ ProductName WRITE SetProductName NOTIFY ProductNameChanged)
			Q_PROPERTY(QString Part MEMBER m_Part READ Part WRITE SetPart NOTIFY PartChanged)
			Q_PROPERTY(RW::SQL::Recept ReceptInstance MEMBER m_Recept READ Recept WRITE SetRecept NOTIFY ReceptChanged)
			Q_CLASSINFO("Version", "0.0.1")

		private:
			QString m_ProductName;
			QString m_Part;
			RW::SQL::Recept m_Recept;
		public:
			Product(Entity *Parent = nullptr);
			~Product();

			QString ProductName(){ return m_ProductName;}
			void SetProductName(QString Product){ m_ProductName = Product; emit ProductNameChanged();}

			QString Part(){ return m_Part; }
			void SetPart(QString Step){ m_Part = Step; emit PartChanged(); }

			RW::SQL::Recept Recept(){ return m_Recept; }
			void SetRecept(RW::SQL::Recept ReceptID){ m_Recept = ReceptID; emit ReceptChanged(); }
		signals:
			void ProductNameChanged();
			void PartChanged();
			void ReceptChanged();
		};
	}
}
