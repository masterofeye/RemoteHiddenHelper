#pragma once
#include "Entity.h"
namespace RW{
	namespace SQL{

		class Instruction :
			public Entity
		{
			Q_OBJECT

			Q_PROPERTY(QString Step MEMBER m_Step READ Step WRITE SetStep NOTIFY StepChanged)
			Q_CLASSINFO("Version", "0.0.1")
		private:
			QString m_Step;

		
		public:
			Instruction(Entity *Parent = nullptr);
			~Instruction();

			QString Step(){ return m_Step; }
			void SetStep(QString Step){ m_Step = Step; emit StepChanged(); }
			

		signals:
			void StepChanged();
		};
	}
}
