#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QSlider>
#include <QLineEdit>
#include <QString>
#include <QStringList>

class DialogCreator : public QDialog
{
    Q_OBJECT

public:
    static QDialog* createDialog(QString widgetName, QStringList checkboxNames, QStringList radioButtonNames, QStringList sliderNames, QDialog* parent = nullptr);

signals:
    void widgetCloseButtonPressed(QDialog* widget);
};

#endif // DIALOGMANAGER_H