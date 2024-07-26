// widgetManager.h
#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QCheckBox>
#include <QSlider>
#include <QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>

class WidgetCreator : public QWidget
{
	Q_OBJECT
public:
	WidgetCreator(QString widgetName, QStringList checkboxNames, QStringList radioButtonNames, QStringList sliderNames, QWidget* parent = nullptr);
	~WidgetCreator();

	//QWidget createWidget();
signals:
	void widgetCloseButtonPressed(QWidget* widget);		// signal for removing the widget

private:

};

#endif // WIDGETMANAGER_H