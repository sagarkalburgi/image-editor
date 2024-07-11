#include "events.h"

EventHandler::EventHandler(QWidget* parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)), pixelInfoLabel(new QLabel(this))
{
	setScene(scene);
	setAcceptDrops(true);
	setTransformationAnchor(AnchorUnderMouse);  // Anchor zoom to mouse position
	pixelInfoLabel->setStyleSheet("QLabel { background-color : white; color : black; border: 1px solid black}");
	pixelInfoLabel->setFixedSize(120, 40);
	pixelInfoLabel->setVisible(false);
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
		imageWidth = pixmap.width();
		imageHeight = pixmap.height();

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
	if (event->button() == Qt::MiddleButton)
	{
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
	if (panning)
	{
		QPoint delta = event->pos() - lastPanPoint;
		lastPanPoint = event->pos();
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
		verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
		event->accept();
		return;
	}

	if (ctrlPressed && !orignalImage.isNull())
	{
		updatePixelInfo(event->pos());
	}

	QGraphicsView::mouseMoveEvent(event);
}

void EventHandler::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton)
	{
		panning = false;
		setCursor(Qt::ArrowCursor);
		event->accept();
		return;
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void EventHandler::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Control)
	{
		ctrlPressed = true;
		pixelInfoLabel->setVisible(true);
	}
	QGraphicsView::keyPressEvent(event);
}

void EventHandler::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Control)
	{
		ctrlPressed = false;
		pixelInfoLabel->setVisible(false);
	}
	QGraphicsView::keyReleaseEvent(event);
}

void EventHandler::leaveEvent(QEvent* event)
{
	pixelInfoLabel->setVisible(false);
	QGraphicsView::leaveEvent(event);
}

void EventHandler::updatePixelInfo(const QPoint& pos)
{
	QPointF scenePos = mapToScene(pos);
	int x = static_cast<int>(scenePos.x());
	int y = static_cast<int>(scenePos.y());
	if (x >= 0 && x < imageWidth && y >= 0 && y < imageHeight)
	{
		QColor color = orignalImage.toImage().pixelColor(x, y);
		QString info = QString("X: %1, Y: %2<br>"
                               "<span style='color: red;'>R: %3</span>, "
                               "<span style='color: green;'>G: %4</span>, "
							   "<span style='color: blue;'>B: %5</span>")
						.arg(x)
						.arg(y)
						.arg(color.red())
						.arg(color.green())
						.arg(color.blue());
		pixelInfoLabel->setTextFormat(Qt::RichText);
		pixelInfoLabel->setText(info);

		// Calculate new position for the label
		int labelWidth = pixelInfoLabel->width();
		int labelHeight = pixelInfoLabel->height();
		int newX = pos.x() + 10;
		int newY = pos.y() + 10;

		// Adjust if the label goes out of the right edge
		if (newX + labelWidth + 20 > this->width())
		{
			newX = pos.x() - labelWidth - 10;
		}

		// Adjust if the label goes out of the bottom edge
		if (newY + labelHeight + 20 > this->height())
		{
			newY = pos.y() - labelHeight - 10;
		}

		pixelInfoLabel->move(newX, newY);
		pixelInfoLabel->setVisible(true);
	}
	else
	{
		pixelInfoLabel->setVisible(false);
	}
}