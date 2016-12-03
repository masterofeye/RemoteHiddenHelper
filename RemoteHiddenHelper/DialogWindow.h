#pragma once
#include <QMainWindow>

namespace Ui {
	class RemoteHiddenHelperClass;
}

class DialogWindow : public QMainWindow
{
    Q_OBJECT
public:
	explicit DialogWindow(QWidget *parent = 0);
	~DialogWindow();
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
private:
	Ui::RemoteHiddenHelperClass *ui;
};

