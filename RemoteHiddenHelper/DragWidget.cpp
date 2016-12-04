#include "DragWidget.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <qdebug.h>

DragWidget::DragWidget(QWidget *Parent) : QFrame(Parent)
{
	setAcceptDrops(true);
}


DragWidget::~DragWidget()
{
}

void dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

void DragWidget::dropEvent(QDropEvent* event)
{
	const QMimeData* mimeData = event->mimeData();

	// check for our needed mime type, here a file or a list of files
	if (mimeData->hasUrls())
	{
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();

		// extract the local paths of the files
		for (int i = 0; i < urlList.size() && i < 32; +i)
		{
			pathList.append(urlList.at(i).toLocalFile());
		}

		// call a function to open the files
		qDebug() << pathList;
	}
}