#include <QApplication>

#include "imageeditor.h"
#include "logging.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set the custom message handler
    qInstallMessageHandler(customLogMessageHandler);

    imageeditor editor;
    editor.show();

    int result = app.exec();

    return result;
}