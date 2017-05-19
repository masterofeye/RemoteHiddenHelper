#include "MessageWindow.h"
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <QTextEdit>
#include <QLabel>
#include <qboxlayout.h>
#include <qpixmap.h>
#include <qtimer.h>

MessageWindow::MessageWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Popup);

    m_Message = new QLabel(this);
    m_Message->setWordWrap(true);

    QFont font;
    font.setPointSize(12);

    m_Message->setFont(font);
    m_Icon = new QLabel(this);


    m_Layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
    m_Layout->addWidget(m_Icon, 1, Qt::AlignLeft);
    m_Layout->addWidget(m_Message,4, Qt::AlignLeft);

     
    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout,this, &MessageWindow::OnTimeout);
}


MessageWindow::~MessageWindow()
{
}

MessageWindow::TasklistOrientation MessageWindow::GetTaskListOrientation()
{
    QRect displayRect = QApplication::desktop()->screenGeometry();
    QRect desktopRect = QApplication::desktop()->availableGeometry();

    if (desktopRect.height() < displayRect.height())
    {
        if (desktopRect.y() > displayRect.y())
            return MessageWindow::TasklistOrientation::TOP;
        else
            return MessageWindow::TasklistOrientation::BOTTOM;
    }
    else
    {
        if (desktopRect.x() > displayRect.x())
            return MessageWindow::TasklistOrientation::LEFT;
        else
            return MessageWindow::TasklistOrientation::RIGHT;
    }
}

void MessageWindow::Ballon(quint64 Msecs, QString Message, quint8 Index)
{
    QRect displayRect = QApplication::desktop()->screenGeometry();
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QSize sh = sizeHint();
    
    int width = 400;
    int height = 100;
    int x = displayRect.bottomRight().x();
    int y = displayRect.bottomRight().y();


    MessageWindow::TasklistOrientation orientation = GetTaskListOrientation();
    switch (orientation)
    {
    case MessageWindow::TasklistOrientation::TOP:
        move(x - width, y - height - 20);
        break;
    case MessageWindow::TasklistOrientation::BOTTOM:
        move(x - width, y - height - 20 - (displayRect.height() - desktopRect.height()));
        break;
    case MessageWindow::TasklistOrientation::RIGHT:
        move(x - width - (displayRect.width() - desktopRect.width()), y - height -20);
        break;
    case MessageWindow::TasklistOrientation::LEFT:
        move(x - width, y - height - 20);
        break;
    case MessageWindow::TasklistOrientation::NON:
        break;
    default:
        break;
    }

    resize(width, height);

    Information i = (Information)Index;
    QPixmap mypix(":/RemoteHiddenHelper/info.png");
    switch (i)
    {
    case MessageWindow::Information::INFO:
        mypix.load(":/RemoteHiddenHelper/info.png");
        break;
    case MessageWindow::Information::WARNING:
        mypix.load(":/RemoteHiddenHelper/warning.png");
        break;
    case MessageWindow::Information::ALERT:
        mypix.load(":/RemoteHiddenHelper/alert.png");
        break;
    case MessageWindow::Information::NON:
        break;
    default:
        break;
    }

    if (Msecs > 0)
        m_Timer->start(Msecs);

    mypix = mypix.scaled(QSize(50, 50), Qt::KeepAspectRatio);
    m_Icon->setPixmap(mypix);
    m_Message->setText(Message);
    show();
}


void MessageWindow::OnTimeout()
{
    m_Timer->stop();
    hide();
}

void MessageWindow::mousePressEvent(QMouseEvent *event)
{
    hide();
}