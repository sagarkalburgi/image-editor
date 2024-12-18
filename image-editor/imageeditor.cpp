#include "imageeditor.h"
#include "menu.h"
#include "dialogManager.h"
#include "logging.h"

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

    // Log initialization
    qCInfo(imageEditorLog) << "Image editor initialized";
}

imageeditor::~imageeditor()
{
    delete ui;
    qCInfo(imageEditorLog) << "Image editor destroyed";
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
            qCInfo(imageEditorLog) << "Loaded image:" << fileName;
        }
        else {
            qCWarning(imageEditorLog) << "Failed to load image:" << fileName;
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
		    QDialog* EdgeDialog = DialogCreator::createDialog("EdgeFilter", { "test2", "test1" }, { "Canny", "Sobel" }, { "Threshold" });

            // Add the new widget to the scroll layout
            scrollLayout->addWidget(EdgeDialog);

            // Ensure the widget is visible
            EdgeDialog->exec();
            qCInfo(dialogLog) << "Edge filter dialog opened";
            break;
        }
    case ThresholdAction:
        {
            QDialog* ThresholdDialog = DialogCreator::createDialog("Threshold", {}, { "R", "G", "B"}, {"Threshold"});

            // Add the new widget to the scroll layout
            scrollLayout->addWidget(ThresholdDialog);

            // Ensure the widget is visible
            ThresholdDialog->exec();
            qCInfo(dialogLog) << "Threshold dialog opened";
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
