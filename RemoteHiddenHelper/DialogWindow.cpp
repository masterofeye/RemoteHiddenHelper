#include "DialogWindow.h"
#include "ui_remotehiddenhelper.h"
#include <QCloseEvent>

DialogWindow::DialogWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::RemoteHiddenHelperClass)
{
	ui->setupUi(this);

}

DialogWindow::~DialogWindow()
{
	delete ui;
}

void DialogWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}
