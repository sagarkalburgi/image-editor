#include "events.h"

EventHandler::EventHandler(QWidget* parent) : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
	setScene(scene);
	setAcceptDrops(true);
	setTransformationAnchor(AnchorUnderMouse);  // Anchor zoom to mouse position
}

void EventHandler::dragEnterEvent(QDragEnterEvent* event)
{
	QDragEnterEvent* DragEnterEvent = static_cast<QDragEnterEvent*>(event);
	if (DragEnterEvent->mimeData()->hasUrls())
	{
		DragEnterEvent->acceptProposedAction();
	}
}

void EventHandler::dragLeaveEvent(QDragLeaveEvent* event)
{
	event->accept();
}

void EventHandler::dragMoveEvent(QDragMoveEvent* event)
{
	event->accept();
	event->acceptProposedAction();
}

void EventHandler::dropEvent(QDropEvent* event)
{
	if (event->source() == this) return;

	QDropEvent* DropEvent = static_cast<QDropEvent*>(event);
	if (!DropEvent->mimeData()->hasUrls()) return;

	QList<QUrl> urllist = DropEvent->mimeData()->urls();

	foreach(QUrl url, urllist)
	{
		// check if its local file
		if (!url.isLocalFile()) continue;

		QString FilePath = url.toLocalFile();
		QPixmap pixmap(FilePath);

		// check if image is not null
		if (pixmap.isNull() == true) continue;

		// store the pixmap
		orignalImage = pixmap;

		// clear scene if image already exists
		if (scene->items().count() > 0) scene->clear();

		// display image
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);

		scene->addItem(item);
		this->setScene(scene);
		this->fitInView(item, Qt::KeepAspectRatio);

		DropEvent->acceptProposedAction();
	}
}

void EventHandler::wheelEvent(QWheelEvent* event)
{
	if (event->angleDelta().y() > 0)
	{
		// Zoom in
		scale(scaleFactor, scaleFactor);
	}
	else
	{
		// Zoom out
		scale(1.0 / scaleFactor, 1.0 / scaleFactor);
	}
}

void EventHandler::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton) {
		panning = true;
		lastPanPoint = event->pos();
		setCursor(Qt::ClosedHandCursor);
		event->accept();
		return;
	}
	QGraphicsView::mousePressEvent(event);
}

void EventHandler::mouseMoveEvent(QMouseEvent* event)
{
	if (panning) {
		QPoint delta = event->pos() - lastPanPoint;
		lastPanPoint = event->pos();
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
		verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
		event->accept();
		return;
	}
	QGraphicsView::mouseMoveEvent(event);
}

void EventHandler::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton) {
		panning = false;
		setCursor(Qt::ArrowCursor);
		event->accept();
		return;
	}
	QGraphicsView::mouseReleaseEvent(event);
}
