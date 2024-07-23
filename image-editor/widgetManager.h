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

class WidgetCreator : public QWidget
{
public:
	WidgetCreator(QString widgetName, QStringList checkboxNames, QStringList radioButtonNames, QStringList sliderNames, QWidget* parent = nullptr);
	~WidgetCreator();

	//QWidget createWidget();

private:

};

#endif // WIDGETMANAGER_H