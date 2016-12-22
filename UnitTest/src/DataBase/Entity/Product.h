#pragma once

#include "Entity.h"
namespace RW{
	namespace SQL{
		class ProductPrivate;
		class Recept;
		class Product :
			public Entity
		{
			Q_OBJECT
			Q_PROPERTY(QString ProductName READ ProductName WRITE SetProductName NOTIFY ProductNameChanged)
			Q_PROPERTY(QString Part READ Part WRITE SetPart NOTIFY PartChanged)
			//Q_PROPERTY(RW::SQL::Recept ReceptInstance READ Recept WRITE SetRecept NOTIFY ReceptChanged)
			Q_CLASSINFO("Version", "0.0.1")

		private:
			ProductPrivate* d_ptr;
			Q_DECLARE_PRIVATE(Product);
		public:
			Product(Entity *Parent = nullptr);
			~Product();

			QString ProductName();
			void SetProductName(QString Product);

			QString Part();
			void SetPart(QString Step);

			RW::SQL::Recept& Recept();
			void SetRecept(RW::SQL::Recept &ReceptID);
		signals:
			void ProductNameChanged();
			void PartChanged();
			void ReceptChanged();
		};
	}
}
