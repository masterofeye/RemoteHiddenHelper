#include "MessageWindow.h"
#include <qapplication.h>
#include <qdesktopwidget.h>


MessageWindow::MessageWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window);
    resize(400, 100);
}


MessageWindow::~MessageWindow()
{
}

void MessageWindow::Ballon(quint64 Msecs)
{
    QRect src = QApplication::desktop()->screenGeometry();
    QSize sh = sizeHint();
    
    move(100,100);
    setGeometry(100, 100, 100, 100);
    showNormal();
}
