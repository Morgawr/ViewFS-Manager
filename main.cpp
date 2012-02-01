#include <QtGui/QApplication>
#include "managerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ManagerWindow w;
    w.show();

    return a.exec();
}
