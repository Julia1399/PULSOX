#include "mainwindow.h"
#include <QApplication>
#include <dialog.h>
#include <QDateTime>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Dialog dialog;
    dialog.show();

    return a.exec();


}
