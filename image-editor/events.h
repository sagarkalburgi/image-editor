#ifndef EVENTS_H
#define EVENTS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QWheelEvent>
#include <QMimeData>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>

/// <summary>
/// Drag and Drop Handler class
/// </summary>
class EventHandler : public QGraphicsView
{
	Q_OBJECT

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="view"></param>
	/// <param name="scene"></param>
	explicit EventHandler(QWidget* parent = nullptr);

protected:
	/// <summary>
	/// Event for handling drag enter
	/// </summary>
	/// <param name="event"></param>
	void dragEnterEvent(QDragEnterEvent* event) override;

	/// <summary>
	/// Event for handling drag leave
	/// </summary>
	/// <param name="event"></param>
	void dragLeaveEvent(QDragLeaveEvent* event) override;

	/// <summary>
	/// Event for handling drag move
	/// </summary>
	/// <param name="event"></param>
	void dragMoveEvent(QDragMoveEvent* event) override;

	/// <summary>
	/// Event for handling drop
	/// </summary>
	/// <param name="event"></param>
	void dropEvent(QDropEvent* event) override;

	/// <summary>
	/// Event for wheel actions
	/// </summary>
	/// <param name="event"></param>
	void wheelEvent(QWheelEvent* event);

	/// <summary>
	/// Event for mouse wheel press
	/// </summary>
	/// <param name="event"></param>
	void mousePressEvent(QMouseEvent* event) override;

	/// <summary>
	/// Event for mouse move
	/// </summary>
	/// <param name="event"></param>
	void mouseMoveEvent(QMouseEvent* event) override;

	/// <summary>
	/// Event for mouse wheel release
	/// </summary>
	/// <param name="event"></param>
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QGraphicsScene* scene;
	QPixmap orignalImage;
	double scaleFactor = 1.1; // Scale factor for zooming

	// For panning
	bool panning = false;
	QPoint lastPanPoint;
};

#endif // EVENTS_H
