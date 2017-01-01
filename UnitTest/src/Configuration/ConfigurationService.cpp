#include "ConfigurationService.h"

#include <QMap>
#include <qmetaobject.h>
#include <qdebug.h>
#include <qvariant.h>

#include "ConfigurationFacade.h"

#define REGISTER_SLOT "OnConfiguration"
#define REGISTER_SIGNAL "ConfigurationChanged"


namespace RW{
	namespace CORE{
		ConfigurationService::ConfigurationService(QObject *Parent) : QObject(Parent),
			m_UserSettings(new QMap<ConfigurationKey, QVariant>()),
			m_ApplicationSettings(new QMap<ConfigurationKey, QVariant>()),
			m_NotificationList(new QMultiMap<QObject*, QString>())
		{
			m_ServiceLayer = new ConfigurationFacade(this);
			connect(this, &ConfigurationService::ReadOrUpdateAppSettings, m_ServiceLayer, &ConfigurationFacade::OnReadOrUpdateAppSettings);
			connect(this, &ConfigurationService::ReadOrUpdateUserSettings, m_ServiceLayer, &ConfigurationFacade::OnReadOrUpdateUserSettings);
		}


		ConfigurationService::~ConfigurationService()
		{
			delete m_UserSettings;
			delete m_ApplicationSettings;
			delete m_NotificationList;
		}

		/**
		@brief Verbindet den REGISTER_SLOT Slot mit dem ConfigurationChanged Signal um alle Receiver darüber zu informieren wenn sich Settings geändert haben. 
		Weiterhin werden alle ConfigurationChanged Signale vom Receiver mit dem OnChangeConfiguration Slot verbunden. Die ermöglicht es auch für die Receiver 
		Daten in der Configuration zu hinterlegen. 
		@param Receiver Der Client der Information aus der Konfiguration benögigt und über Updates informiert werden will. Selbiger muss in der @see ConfigurationReceiver
		List eingetragen sein. 
		*/
		void ConfigurationService::Register(QObject *Receiver, QString Key)
		{
			const QMetaObject* metaObject = Receiver->metaObject();
			QStringList methods;
			for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
				if (metaObject->method(i).methodType() == QMetaMethod::Slot) {
					if (metaObject->method(i).name() == REGISTER_SLOT)
					{
						if (!connect(this, QMetaMethod::fromSignal(&ConfigurationService::ConfigurationChanged), Receiver, metaObject->method(i)))
						{
							qDebug() << "Connect zwischen ConfigurationChanged und " << metaObject->method(i).methodSignature() << " war nicht erfolgreicht";
						}
					}
				}
				if (metaObject->method(i).methodType() == QMetaMethod::Signal)
				{
					if (metaObject->method(i).name() == REGISTER_SIGNAL)
					{
						const QMetaObject* currentMetaObject = this->metaObject();
						int functionIndex = currentMetaObject->indexOfSlot("OnChangeConfiguration()");
						QMetaMethod slot = currentMetaObject->method(functionIndex);
						if(!connect(Receiver, metaObject->method(i), this, slot))
						{
							qDebug() << "Connect zwischen ConfigurationChanged und OnChangeConfiguration war nicht erfolgreicht";
						}
					}
				}
			}
		}

		void ConfigurationService::UnregisterAll()
		{
			
		}

		void ConfigurationService::OnProcessMessage(QVariant Data)
		{
		
		}

		void ConfigurationService::OnChangeConfiguration(TypeOfCfgChange Type, ConfigurationReceiver Receiver, QVariant Data)
		{
		
		}

	}
}