#pragma once
#include "Repository.h"
namespace RW{
	namespace SQL{
		class Repository :
			public Repository
		{
			Q_OBJECT
		public:
			Repository(QObject* Parent = nullptr);
			~Repository();
		};
	}
}
