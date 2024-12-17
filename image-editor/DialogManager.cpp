#include "dialogManager.h"

QDialog* DialogCreator::createDialog(QString dialogName, QStringList checkboxNames, QStringList radioButtonNames, QStringList sliderNames, QDialog* parent)
{
    QDialog* newDialog = new QDialog();
    newDialog->setStyleSheet("QDialog { border: 2px solid black; }");
    newDialog->setFixedSize(175, 120);

    // Create a vertical layout for the new dialog
    QVBoxLayout* vLayout = new QVBoxLayout(newDialog);
    vLayout->setSpacing(10);  // Set spacing between elements in the vertical layout
    vLayout->setContentsMargins(10, 10, 10, 10);  // Set margins around the layout

    // Create a horizontal layout for the label and close button
    QHBoxLayout* labelClosebuttonLayout = new QHBoxLayout();
    labelClosebuttonLayout->setSpacing(5);  // Space between label and close button

    // Create the label and add it to the horizontal layout
    QLabel* label = new QLabel(dialogName, newDialog);
    labelClosebuttonLayout->addWidget(label);

    // Create the close button and add it to the horizontal layout
    QPushButton* closeButton = new QPushButton("Close", newDialog);
    QObject::connect(closeButton, &QPushButton::clicked, newDialog, &QDialog::close);
    closeButton->setFixedSize(50, 25);
    labelClosebuttonLayout->addWidget(closeButton);

    // Add the label and close button layout to the vertical layout
    vLayout->addLayout(labelClosebuttonLayout);

    // Create a horizontal layout for the checkboxes
    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->setSpacing(5);  // Space between checkboxes

    // Create the checkbox and add it to the horizontal layout
    foreach(const QString & checkbox, checkboxNames) {
        QCheckBox* checkBox = new QCheckBox(checkbox, newDialog);
        checkBoxLayout->addWidget(checkBox);
    }

    // Add the label and checkbox layout to the vertical layout
    vLayout->addLayout(checkBoxLayout);

    // Create a horizontal layout for the radio buttons
    QHBoxLayout* radioButtonLayout = new QHBoxLayout();
    radioButtonLayout->setSpacing(5);  // Space between radio buttons

    // Create the radio buttons and add them to the horizontal layout
    foreach(const QString & radioButtonName, radioButtonNames) {
        QRadioButton* radioButton = new QRadioButton(radioButtonName, newDialog);
        radioButtonLayout->addWidget(radioButton);
    }

    // Add the radio button layout to the vertical layout
    vLayout->addLayout(radioButtonLayout);

    // Create a vertical layout for the sliders
    QVBoxLayout* sliderLayout = new QVBoxLayout();
    sliderLayout->setSpacing(10);  // Set space between sliders

    // Create the horizontal slider and add it to the horizontal layout
    foreach(const QString & sliderName, sliderNames) {
        // Create a horizontal layout for the sliders and line edit
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setSpacing(5);  // Space between label and checkboxes

        // Create slider and add it to hlayout
        QSlider* slider = new QSlider(Qt::Horizontal, newDialog);
        slider->setFixedSize(120, 20);
        hLayout->addWidget(slider);

        // Create the line edit, set size and add it to the horizontal layout
        QLineEdit* lineEdit = new QLineEdit(newDialog);
        lineEdit->setFixedSize(20, 20);
        hLayout->addWidget(lineEdit);

        // Add it slider and textbox to sliderlayout
        sliderLayout->addLayout(hLayout);

        // Set the size policy of newDialog to expanding
        newDialog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Set objectname
        newDialog->setObjectName(dialogName);
    }

    // Add the horizontal layout to the vertical layout
    vLayout->addLayout(sliderLayout);
    return newDialog;
}
