#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_imageeditor.h"

class imageeditor : public QMainWindow
{
    Q_OBJECT

public:
    imageeditor(QWidget *parent = nullptr);
    ~imageeditor();

private:
    Ui::mainWindow ui;
};
