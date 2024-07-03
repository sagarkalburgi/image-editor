#include "imageeditor.h"
#include "events.h"

imageeditor::imageeditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    connect(ui->actionopen, &QAction::triggered, this, &imageeditor::openFile);

    // drag and drop event
    auto dropEvent = new Drag_Drop_Image(this);
    ui->graphicsView->setParent(nullptr);
    ui->graphicsView = dropEvent;
    setCentralWidget(ui->graphicsView);
}

imageeditor::~imageeditor()
{}

void imageeditor::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Image Files (*.png *.jpg *.bmp *.gif *.jpeg *tif)"));
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (!image.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene(this);
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(item);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
        }
        else {
            qDebug() << "Failed to load image:" << fileName;
        }
    }
}