#include "ElementConfiguration.h"
#include "ElementConfiguration_p.h"
#include "ElementType.h"
#include "qdebug.h"

namespace RW{
	namespace SQL{

		ElementConfigurationPrivate::ElementConfigurationPrivate(ElementConfiguration* Parent) :
			//QObject(Parent),
			q_ptr(Parent),
			m_DisplayName(""),
			m_Function(""),
			m_GroupName(""),
			m_Type(),
			m_Name("")
		{
			qDebug() << "ctor ElementConfigurationPrivate";
		}

		ElementConfigurationPrivate::~ElementConfigurationPrivate()
		{
			qDebug() << "~ctor ElementConfigurationPrivate";
		}


		ElementConfiguration::ElementConfiguration(Entity *Parent) : Entity(Parent),
			d_ptr(new ElementConfigurationPrivate(this))
		{
			qDebug() << "ctor ElementConfiguration ";
		}

		ElementConfiguration::~ElementConfiguration()
		{
			qDebug() << "delete ElementConfiguration";
		}

		ElementConfiguration::ElementConfiguration(const ElementConfiguration& other) : d_ptr(other.d_ptr)
		{
			qDebug() << "copy ElementConfiguration";
		}
		ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration& other)
		{
			qDebug() << "Copy Operator RemoteWorkstation";
			std::swap(d_ptr, const_cast<ElementConfigurationPrivate*>(other.d_ptr));
			qDebug() << "copy operator ElementConfiguration";
			return *this;
		}


		ElementConfiguration::ElementConfiguration(ElementConfiguration&& other) : d_ptr(other.d_ptr)
		{
			qDebug() << "move ElementConfiguration";
			other.d_ptr = nullptr;
			
		}
		ElementConfiguration& ElementConfiguration::operator=(ElementConfiguration&& other)
		{
			qDebug() << "move operator ElementConfiguration";
			std::swap(d_ptr, other.d_ptr);
			delete other.d_ptr;
			other.d_ptr = nullptr;
			return *this;
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

		QString ElementConfiguration::GroupName()
		{
			Q_D(ElementConfiguration);
			return d_ptr->m_GroupName;
		}
		void ElementConfiguration::SetGroupName(QString GroupName)
		{
			Q_D(ElementConfiguration);
			d->m_GroupName = GroupName;
			emit GroupNameChanged();
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
