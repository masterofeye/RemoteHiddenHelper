#pragma once
#include "qobject.h"
class CommunicationServer :
	public QObject
{
	Q_OBJECT
public:
	CommunicationServer(QObject *Parent = nullptr);
	~CommunicationServer();
};

