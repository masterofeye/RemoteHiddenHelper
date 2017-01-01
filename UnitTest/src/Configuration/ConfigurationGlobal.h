#pragma once
#include "qobject.h"
#include <QMetaType>
#include <QVariant>


namespace RW{

	enum class ConfigurationKey
	{
		RemoteWorkstations,

	};

	enum class TypeOfCfgChange
	{
		Loaded,
		Updated
	};

	enum class ConfigurationReceiver
	{
		FlashManager,
		PowerStripe,
		PowerSupply,
		RemoteBox

	};






}