#pragma once

// Qt
#include <QtWidgets/QMainWindow>
#include "ui_imageeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class imageeditior; }
QT_END_NAMESPACE

/// <summary>
/// image editor UI
/// </summary>
class imageeditor : public QMainWindow
{
    Q_OBJECT

public:
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="parent"></param>
    imageeditor(QWidget *parent = nullptr);

    /// <summary>
    /// Destructor
    /// </summary>
    ~imageeditor();

private:
    Ui::mainWindow *ui;
};
