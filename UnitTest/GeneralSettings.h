#pragma once
#include "Entity.h"

namespace RW
{
	namespace SQL
	{
		class GeneralSettingsPrivate;
		class GeneralSettings :
			public Entity
		{
			Q_OBJECT
			//Q_PROPERTY(QString Step MEMBER m_Step READ Step WRITE SetStep NOTIFY StepChanged)
			Q_CLASSINFO("Version", "0.0.1")
		private:
			GeneralSettingsPrivate* d_ptr;
			Q_DECLARE_PRIVATE(GeneralSettings);

		public:
			GeneralSettings(Entity *Parent = nullptr);
			~GeneralSettings();

		signals:
		};
	}
}
