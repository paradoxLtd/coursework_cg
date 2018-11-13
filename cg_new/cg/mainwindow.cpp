#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window_size.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QImage(WIDTH_WIN, HEIGHT_WIN, QImage::Format_RGB32);
    image->fill(Qt::white);
    ui->widget = new Bitmap(ui->widget);
    ui->widget->resize(WIDTH_WIN, HEIGHT_WIN);
    ui->widget->setImage(*image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
