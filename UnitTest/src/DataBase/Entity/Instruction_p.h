#pragma once
#include <qobject.h>

namespace RW{
	namespace SQL{

		class Instruction;
		class InstructionPrivate : public QObject
		{
			Q_OBJECT
				Q_DISABLE_COPY(InstructionPrivate)
				Q_DECLARE_PUBLIC(Instruction)
		private:
			Instruction * const q_ptr;

		public:
			QString m_Step;
		public:
			InstructionPrivate(Instruction* QPointer);
			~InstructionPrivate();

		signals:
			void StepChanged();

		};


	}
}