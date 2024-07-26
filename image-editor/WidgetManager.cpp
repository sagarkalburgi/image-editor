#include "widgetManager.h"

WidgetCreator::WidgetCreator(QString widgetName, QStringList checkboxNames, QStringList radioButtonNames, QStringList sliderNames, QWidget* parent) : QWidget(parent)
{
    // Create a new widget to hold all elements
    QWidget* newWidget = new QWidget(this);

    // Set dimensions for the new widget
    //newWidget->setFixedSize(200, 80);

    // Set the border style for the new widget
    newWidget->setStyleSheet("QWidget#newWidget border: 2px solid black;");

    // Create a vertical layout for the new widget
    QVBoxLayout* vLayout = new QVBoxLayout(newWidget);
    vLayout->setSpacing(10);  // Set spacing between elements in the vertical layout
    vLayout->setContentsMargins(10, 10, 10, 10);  // Set margins around the layout

    // Create a horizontal layout for the label and close button
    QHBoxLayout* labelClosebuttonLayout = new QHBoxLayout();
    labelClosebuttonLayout->setSpacing(5);  // Space between label and close button

    // Create the label and add it to the horizontal layout
    QLabel* label = new QLabel(widgetName, newWidget);
    labelClosebuttonLayout->addWidget(label);

    // Create the close button and add it to the horizontal layout
    QPushButton* closeButton = new QPushButton("Close", newWidget);
    closeButton->setFixedSize(25, 25);
    labelClosebuttonLayout->addWidget(closeButton);

    // Connect the close button to emit the widgetClosed signal
    connect(closeButton, &QPushButton::clicked, [this]() { emit widgetCloseButtonPressed(this); });

    // Add the label and close button layout to the vertical layout
    vLayout->addLayout(labelClosebuttonLayout);

    // Create a horizontal layout for the check box
    QHBoxLayout* CheckBoxLayout = new QHBoxLayout();
    CheckBoxLayout->setSpacing(5);  // Space between check box

    // Create a horizontal layout for the checkboxes
    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->setSpacing(5);  // Space between checkboxes

    // Create the checkbox and add it to the horizontal layout
    foreach(const QString & checkbox, checkboxNames) {
        QCheckBox* checkBox = new QCheckBox(checkbox, newWidget);
        CheckBoxLayout->addWidget(checkBox);
    }

    // Add the label and checkbox layout to the vertical layout
    vLayout->addLayout(CheckBoxLayout);

    // Create a horizontal layout for the radio buttons
    QHBoxLayout* radioButtonLayout = new QHBoxLayout();
    radioButtonLayout->setSpacing(5);  // Space between radio buttons

    // Create the radio buttons and add them to the horizontal layout
    foreach(const QString& radioButtonName, radioButtonNames) {
        QRadioButton* radioButton = new QRadioButton(radioButtonName, newWidget);
        radioButtonLayout->addWidget(radioButton);
    }

    // Add the radio button layout to the vertical layout
    vLayout->addLayout(radioButtonLayout);

    // Create a vertical layout for the sliders
    QVBoxLayout* sliderLayout = new QVBoxLayout();
    sliderLayout->setSpacing(10);  // Set space between sliders

    // Create the horizontal slider and add it to the horizontal layout
    foreach(const QString& sliderName, sliderNames) {
        // Create a horizontal layout for the sliders and line edit
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setSpacing(5);  // Space between label and checkboxes

        // Create slider and add it to hlayout
        QSlider* slider = new QSlider(Qt::Horizontal, newWidget);
        slider->setFixedSize(120, 20);
        hLayout->addWidget(slider);

        // Create the line edit, set size and add it to the horizontal layout
        QLineEdit* lineEdit = new QLineEdit(newWidget);
        lineEdit->setFixedSize(20, 20);
        hLayout->addWidget(lineEdit);

        // Add it slider and textbox to sliderlayout
        sliderLayout->addLayout(hLayout);

        // Set the size policy of newWidget to expanding
        newWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Set objectname
        newWidget->setObjectName(widgetName);
    }

    // Add the horizontal layout to the vertical layout
    vLayout->addLayout(sliderLayout);
}

WidgetCreator::~WidgetCreator()
{
}
