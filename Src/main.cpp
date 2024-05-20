#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("AshenvaleZX");
    QCoreApplication::setApplicationName("ZXEngine Hub");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
