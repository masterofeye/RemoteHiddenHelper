#include "DialogWindow.h"
#include "ui_remotehiddenhelper.h"
#include <QCloseEvent>
#include "DragWidget.h"

DialogWindow::DialogWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::RemoteHiddenHelperClass)
{
	ui->setupUi(this);
	DragWidget* w = new DragWidget(this);
	ui->hbDragLayout->addWidget(w);

}

DialogWindow::~DialogWindow()
{
	delete ui;
}

void DialogWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}
