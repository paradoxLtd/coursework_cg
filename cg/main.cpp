#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>

#include <QTextStream>
#include <QTextCodec>

#include "Loader.h"



int main(int argc, char *argv[])
{
    //setlocale(LC_ALL, "Russian");

    //QApplication a(argc, argv);

    //MainWindow w;
    //w.show();

    Loader::debug();

    return 0;
    //return a.exec();
}
