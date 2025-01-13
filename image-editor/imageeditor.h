#pragma once

// Qt
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QAction>
#include <QDebug>
#include <QMenu>

#include "ui_imageeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
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

private slots:
    void openFile(); // Slot to handle file opeing
    void onMenuActionTriggered();  // Generic slot for new actions
	void updateLogLabel(const QString& message);  // Slot to update the log label

private:
    Ui::mainWindow* ui;
    QVBoxLayout* scrollLayout;
    void setupMenuBar();  // Declare a function to setup the menu bar
};
