#ifndef EVENTS_H
#define EVENTS_H

// Qt
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QWidget>
#include <QMimeData>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>

/// <summary>
/// eventclass
/// </summary>
class Events
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	Events();
};

/// <summary>
/// 
/// </summary>
class Drag_Drop_Image : public QGraphicsView
{
	Q_OBJECT
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="parent"></param>
	explicit Drag_Drop_Image(QWidget* parent = nullptr);

protected:
	/// <summary>
	/// Drag enter event
	/// </summary>
	/// <param name="event"></param>
	void dragEnterEvent(QDragEnterEvent* event);
	/// <summary>
	/// Drag leave event
	/// </summary>
	/// <param name="event"></param>
	void dragLeaveEvent(QDragLeaveEvent* event);
	/// <summary>
	/// Drag move event
	/// </summary>
	/// <param name="event"></param>
	void dragMoveEvent(QDragMoveEvent* event);
	/// <summary>
	/// Drop event
	/// </summary>
	/// <param name="event"></param>
	void dropEvent(QDropEvent* event);

protected:
	QGraphicsScene* scene;
};

#endif // !EVENTS_H
