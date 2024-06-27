#include "events.h"

Drag_Drop_Image::Drag_Drop_Image(QWidget* parent) : QGraphicsView(parent)
{
	setAcceptDrops(true);
	scene = new QGraphicsScene(this);
	setScene(scene);
	viewport()->installEventFilter(this);
}

void Drag_Drop_Image::dragEnterEvent(QDragEnterEvent* event)
{
	QDragEnterEvent* DragEnterEvent = static_cast<QDragEnterEvent*>(event);
	if (DragEnterEvent->mimeData()->hasUrls())
	{
		DragEnterEvent->acceptProposedAction();
	}
}

void Drag_Drop_Image::dragLeaveEvent(QDragLeaveEvent* event)
{
	event->accept();
}

void Drag_Drop_Image::dragMoveEvent(QDragMoveEvent* event)
{
	event->accept();
	event->acceptProposedAction();
}

void Drag_Drop_Image::dropEvent(QDropEvent* event)
{
	if (event->source() == this) return;

	QDropEvent *DropEvent = static_cast<QDropEvent*>(event);
	if (!DropEvent->mimeData()->hasUrls()) return;

	QList<QUrl> urllist = DropEvent->mimeData()->urls();

	foreach (QUrl url, urllist)
	{
		// check if its local file
		if (!url.isLocalFile()) continue;

		QString FilePath = url.toLocalFile();
		QPixmap pixmap(FilePath);

		// check if image is not null
		if (pixmap.isNull() == true) continue;

		// clear scene if image already exists
		if (scene->items().count() > 0) scene->clear();

		// display image
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);

		scene->setSceneRect(pixmap.rect());
		setSceneRect(scene->sceneRect());
		fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

		scene->addItem(item);
		DropEvent->acceptProposedAction();
	}
}

Events::Events()
{
}
