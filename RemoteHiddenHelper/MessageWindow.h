#pragma once
#include "qwidget.h"
class MessageWindow :
    public QWidget
{
    Q_OBJECT
public:
    MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();

    void Ballon(quint64 Msecs);
};

