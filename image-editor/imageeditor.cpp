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

    // Connect the log message signal to the slot
    connect(&Logger::instance(), &Logger::newLogMessage, this, &imageeditor::updateLogLabel);
}

imageeditor::~imageeditor()
{
    qCInfo(imageEditorLog) << "Image editor destroyed";
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
	if (actionName == "Info") return InfoAction;
    if (actionName == "Version") return VersionAction;
    return UnknownAction;
}

void imageeditor::onMenuOptionsTriggered()
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

void imageeditor::onMenuHelpTriggered()
{
    QAction* action = qobject_cast<QAction*>(sender());

    ActionName actionName = getActionFromString(action->text());
    switch (actionName)
    {
    case InfoAction:
        {
		    // Display information about the project
            QString infoText = R"(
            <h2>Project Description</h2>
            <p>The image-editor project is a simple and intuitive tool for editing images. It provides a variety of features such as cropping, resizing, rotating, and applying filters to enhance your photos. The goal of this project is to offer an easy-to-use interface for users to quickly edit their images without needing advanced photo editing skills.</p>

            <h2>Code Generation</h2>
            <p>Additionally, this tool can also be used to generate code in C++ or Python for the edits performed on the image. This feature allows developers to automate image processing tasks by integrating the generated code into their projects.</p>
        )";
            QMessageBox::information(this, "Infomation", infoText);
            break;
        }
    case VersionAction:
        {
		    // Display the version of the project
            QMessageBox::information(this, "Version", "Image Editor Version 1.0.0");
            break;
        }
    case TutorialAction:
        break;
    default:
        break;
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
    QMenu* optionsMenu = new QMenu("Options", this);
    foreach(const QString & menuItemOptions, MenuOptions) {
        QAction* action = new QAction(menuItemOptions, this);
        optionsMenu->addAction(action);
        connect(action, &QAction::triggered, this, &imageeditor::onMenuOptionsTriggered);
    }
    ui->menuBar->addMenu(optionsMenu);

	// help menu bar updating
	QMenu* helpMenu = new QMenu("Help", this);
    foreach(const QString & menuItemHelp, MenuHelp) {
        QAction* action = new QAction(menuItemHelp, this);
        helpMenu->addAction(action);
        connect(action, &QAction::triggered, this, &imageeditor::onMenuHelpTriggered);
	}
    ui->menuBar->addMenu(helpMenu);
}
