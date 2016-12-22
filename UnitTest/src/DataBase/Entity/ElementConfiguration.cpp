#include "ElementConfiguration.h"
#include "ElementConfiguration_p.h"
#include "ElementType.h"

namespace RW{
	namespace SQL{

		ElementConfigurationPrivate::ElementConfigurationPrivate(ElementConfiguration* Parent) :
			QObject(Parent),
			q_ptr(Parent),
			m_DisplayName(""),
			m_Function(""),
			m_Group(""),
			m_Type(),
			m_Name("")
		{
		}

		ElementConfigurationPrivate::~ElementConfigurationPrivate()
		{
		}


		ElementConfiguration::ElementConfiguration(Entity *Parent) : Entity(Parent),
			d_ptr(new ElementConfigurationPrivate(this))
		{
		}

		ElementConfiguration::~ElementConfiguration()
		{
			delete d_ptr;
		}


		ElementType& ElementConfiguration::Type()
		{
			Q_D(ElementConfiguration);
			return d->m_Type;
		}
		void ElementConfiguration::SetType(ElementType &Type)
		{
			Q_D(ElementConfiguration);
			d->m_Type = Type;
			emit TypeChanged();
		}

		QString ElementConfiguration::DisplayName()
		{ 
			Q_D(ElementConfiguration);
			return d->m_DisplayName;
		}

		void ElementConfiguration::SetDisplayName(QString DisplayName)
		{ 
			Q_D(ElementConfiguration);
			d->m_DisplayName = DisplayName;
			emit DisplayNameChanged();
		}

		QString ElementConfiguration::Name(){
			Q_D(ElementConfiguration);
			return d->m_Name;
		}

		void ElementConfiguration::SetName(QString Name)
		{ 
			Q_D(ElementConfiguration);
			d->m_Name = Name;
			emit NameChanged();
		}

		QString ElementConfiguration::Group()
		{
			Q_D(ElementConfiguration);
			return d_ptr->m_Group;
		}
		void ElementConfiguration::SetGroup(QString Group)
		{
			Q_D(ElementConfiguration);
			d->m_Group = Group;
			emit GroupChanged();
		}

		QString ElementConfiguration::Function()
		{
			Q_D(ElementConfiguration);
			return d->m_Function;
		}
		void ElementConfiguration::SetFunction(QString Function)
		{ 
			Q_D(ElementConfiguration);
			d->m_Function = Function;
			emit FunctionChanged();
		}
		
	}
}
