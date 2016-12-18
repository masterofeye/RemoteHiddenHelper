#pragma once
#include "DataFactory.h"
namespace RW{
	namespace SQL{
		class InstructionFactory :
			public DataFactory
		{
		public:
			InstructionFactory(QObject *Parent = nullptr);
			~InstructionFactory();

			/*
			@brief Liefert eine Instanz des passenden DataMappers zur�ck.
			Der beste Weg hier ist einen Adresse auf das Element zur�ck zu geben, weil 
			die Factory nichts �ber den DataMapper wissen muss und es keine Verwirrung �ber 
			das L�schen des Elementes gibt. Der Aufrufer ist n�mlich verantwortlich f�r das L�schen.
			*/
			static DataMapper* GetMapper(DataMapper::SourceType Source);
		};
	}
}
