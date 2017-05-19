#pragma once
#include "qwidget.h"

class QTextEdit;
class QLabel;
class QBoxLayout;
class QTimer;

class MessageWindow :
    public QWidget
{
    Q_OBJECT
public:
    enum class TasklistOrientation
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NON
    };

    enum class Information
    {
        INFO,
        WARNING,
        ALERT,
        NON
    };
private:
    QLabel *m_Message = nullptr;
    QLabel *m_Icon = nullptr;
    QBoxLayout *m_Layout = nullptr;
    QTimer *m_Timer = nullptr;
public:
    MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();

    void Ballon(quint64 Msecs, QString Message, quint8 Index);
    TasklistOrientation GetTaskListOrientation();
    void OnTimeout();
protected:
    void mousePressEvent(QMouseEvent *event);
};

