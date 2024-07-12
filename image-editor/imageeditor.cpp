#include "imageeditor.h"
#include "menu.h"

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

void imageeditor::onMenuActionTriggered()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        // Create a new widget to hold all elements
        QWidget* newWidget = new QWidget(this);
        // Set fixed dimensions for the new widget
        newWidget->setFixedSize(200, 50); 

        // Create a vertical layout for the new widget
        QVBoxLayout* vLayout = new QVBoxLayout(newWidget);

        // Create a horizontal layout for the label and checkbox
        QHBoxLayout* labelCheckBoxLayout = new QHBoxLayout();

        // Create the label and add it to the horizontal layout
        QLabel* label = new QLabel("New Edge Control", newWidget);
        labelCheckBoxLayout->addWidget(label);

        // Create the checkbox and add it to the horizontal layout
        QCheckBox* checkBox = new QCheckBox("Enable", newWidget);
        labelCheckBoxLayout->addWidget(checkBox);

        // Add the label and checkbox layout to the vertical layout
        vLayout->addLayout(labelCheckBoxLayout);

        // Create a horizontal layout for the slider and line edit
        QHBoxLayout* hLayout = new QHBoxLayout();

        // Create the horizontal slider and add it to the horizontal layout
        QSlider* slider = new QSlider(Qt::Horizontal, newWidget);
        hLayout->addWidget(slider);

        // Create the line edit and add it to the horizontal layout
        QLineEdit* lineEdit = new QLineEdit(newWidget);
        lineEdit->setFixedSize(20, 20);
        hLayout->addWidget(lineEdit);

        // Add the horizontal layout to the vertical layout
        vLayout->addLayout(hLayout);

        // Add the new widget to the scroll layout
        scrollLayout->addWidget(newWidget);
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