#include "imageeditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imageeditor w;
    w.show();
    return a.exec();
}
