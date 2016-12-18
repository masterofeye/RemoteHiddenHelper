#pragma once
#include "DataFactory.h"
namespace RW{
	namespace SQL{
		class ReceptFactory :
			public DataFactory
		{
		public:
			ReceptFactory(QObject *Parent = nullptr);
			~ReceptFactory();
			/*
			@brief Liefert eine Instanz des passenden DataMappers zurück.
			Der beste Weg hier ist einen Adresse auf das Element zurück zu geben, weil
			die Factory nichts über den DataMapper wissen muss und es keine Verwirrung über
			das Löschen des Elementes gibt. Der Aufrufer ist nämlich verantwortlich für das Löschen.
			*/
			static DataMapper* GetMapper(DataMapper::SourceType Source);
		};
	}
}
