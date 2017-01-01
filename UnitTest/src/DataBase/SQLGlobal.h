#pragma once
namespace RW{
	enum class TypeOfElement
	{
		USB,
		IO,
		RELAY,
		SOUND,
		INVALID
	};

	enum class SourceType
	{
		SQL,
		XML,
		MOCK
	};
	//Q_ENUM(SourceType);
}