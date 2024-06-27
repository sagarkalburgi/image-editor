#include "imageeditor.h"
#include "events.h"

imageeditor::imageeditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    // drag and drop event
    auto dropEvent = new Drag_Drop_Image(this);
    ui->graphicsView->setParent(nullptr);
    ui->graphicsView = dropEvent;
    setCentralWidget(ui->graphicsView);
}

imageeditor::~imageeditor()
{}
