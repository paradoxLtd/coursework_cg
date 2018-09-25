#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>

#include <QTextStream>
#include <QTextCodec>

#include "Loader.h"



int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

<<<<<<< HEAD
    Loader::debug();
=======
    //Loader::debug();
>>>>>>> fda8ebcd0101d695d6bf2f96683f44abc824c00f

    //return 0;
    return a.exec();
}
