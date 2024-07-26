#include "imageeditor.h"
#include "menu.h"
#include "widgetManager.h"

imageeditor::imageeditor(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    // Setup the menu bar
    setupMenuBar();

    // Initialize the layout for the scroll area
    QWidget* scrollAreaWidget = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollAreaWidget);

    ui->scrollArea->setWidget(scrollAreaWidget);
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
            ui->imageWindow->setScene(scene);
            ui->imageWindow->fitInView(item, Qt::KeepAspectRatio);
        }
        else {
            qDebug() << "Failed to load image:" << fileName;
        }
    }
}

ActionName getActionFromString(const QString& actionName) {
    if (actionName == "Edge") return EdgeAction;
    if (actionName == "Threshold") return ThresholdAction;
    if (actionName == "Split") return SplitAction;
    if (actionName == "Paint") return PaintAction;
    return UnknownAction;
}

void imageeditor::onMenuActionTriggered()
{
    QAction* action = qobject_cast<QAction*>(sender());

    ActionName actionName = getActionFromString(action->text());
    switch (actionName)
    {
    case EdgeAction:
        {
            WidgetCreator* EdgeWidget = new WidgetCreator("EdgeFilter", {"test2", "test1"}, {"Canny", "Sobel"}, {"Threshold"});
            // Add the new widget to the scroll layout
            scrollLayout->addWidget(EdgeWidget);

            // Connect the widgetClosed signal to the slot that handles removing the widget
            connect(EdgeWidget, &WidgetCreator::widgetCloseButtonPressed, this, &imageeditor::removeWidgetFromLayout);

            break;
        }
    case ThresholdAction:
        {
            WidgetCreator* EdgeWidget = new WidgetCreator("Threshold", {}, { "R", "G", "B"}, {"Threshold"});
            // Add the new widget to the scroll layout
            scrollLayout->addWidget(EdgeWidget);

            // Connect the widgetClosed signal to the slot that handles removing the widget
            connect(EdgeWidget, &WidgetCreator::widgetCloseButtonPressed, this, &imageeditor::removeWidgetFromLayout);
            break;
        }
    case SplitAction:
        break;
    case PaintAction:
        break;
    case UnknownAction:
        break;
    default:
        break;
    }
}

void imageeditor::setupMenuBar()
{
    // main manu bar options
    for (int i = 0; i < MenuMain.length(); i++)
    {
        // Create a new action
        QAction* action = new QAction(MenuMain[i], this);

        // Add the new action to the existing menu
        ui->menu_main->addAction(action);

        switch (i)
        {
            // connect open action
        case 0:
            connect(action, &QAction::triggered, this, &imageeditor::openFile);
            break;
        default:
            break;
        }

    }

    // options menu bar updating
    QMenu* menu = new QMenu("Options", this);
    foreach(const QString & menuItem, MenuOptions) {
        QAction* action = new QAction(menuItem, this);
        menu->addAction(action);
        connect(action, &QAction::triggered, this, &imageeditor::onMenuActionTriggered);
    }
    ui->menuBar->addMenu(menu);
}

void imageeditor::removeWidgetFromLayout(QWidget* widget)
{
    // Remove the widget from the layout
    scrollLayout->removeWidget(widget);

    // Delete the widget
    widget->deleteLater();
}