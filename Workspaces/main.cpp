#include "workspaces.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Workspaces w;
    w.show();

    return a.exec();
}
