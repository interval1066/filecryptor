#include "include/mainwindow.h"
#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
#ifndef _DEBUG
    QSharedMemory shared("c53d1e4a-7b10-40a2-8a77-7b0f8e1a357a");

    if(!shared.create( 512, QSharedMemory::ReadWrite))
        exit(0);
#endif
    w.show();

    return a.exec();
}
