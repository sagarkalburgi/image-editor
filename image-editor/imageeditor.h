#pragma once

// Qt
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
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
    void onMenuOptionsTriggered();  // Slot for options actions
    void onMenuHelpTriggered();  // Slot for help actions

private:
    Ui::mainWindow* ui;
    QVBoxLayout* scrollLayout;
    void setupMenuBar();  // Declare a function to setup the menu bar
};
