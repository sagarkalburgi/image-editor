#include "imageeditor.h"

imageeditor::imageeditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    connect(ui->actionopen, &QAction::triggered, this, &imageeditor::openFile);
}

imageeditor::~imageeditor()
{
    delete ui;
}

void imageeditor::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Image Files (*.png *.jpg *.bmp *.gif *.jpeg *tif)"));
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (!image.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene(this);
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->clear();
            scene->addItem(item);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
        }
        else {
            qDebug() << "Failed to load image:" << fileName;
        }
    }
}