#pragma once
#include "qframe.h"
class DragWidget : public QFrame
{
	Q_OBJECT
public:
	explicit DragWidget(QWidget *parent = 0);
	~DragWidget();
protected:
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	//void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
};

