#include "mainwindow.h"
#include "smartpointer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.Work();
    return a.exec();
}
