#include "mainwindow.h"
#include <qDebug>
#include "ui_mainwindow.h"
#include "drawer.h"
#include "point.h"
#include "vector.h"
#include "scene.h"
#include "camera.h"
#include "triangle.h"
#include "loader.h"
#include "objectlist.h"
#include "transformation.h"

#include "bitmap.h"
#include "defines.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = new QImage(WIDTH_WIN, HEIGHT_WIN, QImage::Format_RGB32);
    image->fill(Qt::white);
    ui->widget = new Bitmap(ui->widget);
    ui->widget->resize(600, 600);
    ui->widget->setImage(*image);
    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(500); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(rot_fig_timer())); // Подключаем сигнал таймера к нашему слоту

    this->scene = new Scene(ui->widget);
}

float angle = 0;
void MainWindow::rot_fig_timer()
{
    qDebug() << scene->objects.objects.size();
    const RotateOptions rot(angle, 0, 0);
    const RotateX act;
    Transformation::transform(scene->objects.objects[0], act, rot);

    scene->updateCamera();
    scene->updateScene();
    angle+=20;
}



void MainWindow::on_pushButton_clicked()
{
    Loader loader;
    Object object;
    //int err = loader.load(&object, "loader_test_one.obj");
    int err = loader.load(&object, "loader_test_one.obj");
    SET_BIT(object.state, OBJECT_DETAILED);
    std::cout << "error:" << err << " and " << object.state << "\n ";
    //std::cout << object;
    std::cout << object;


    scene->pushObject(object);




    Transformation::transform(scene->camera, Move(), MoveOptions(2,2));
    Transformation::transform(scene->camera, Scale(), ScaleOptions(0,0,0.3));

    scene->updateCamera();
    scene->updateScene();
    //tmr->start();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_camera_left_clicked()
{

    const RotateOptions rot(0, -M_PI / 36, 0);
    const RotateY act;
    Transformation::transform(scene->camera, act, rot);

    scene->updateCamera();
    scene->updateScene();

}

void MainWindow::on_camera_right_clicked()
{
    const RotateOptions rot(0, M_PI / 36, 0);
    const RotateY act;
    Transformation::transform(scene->camera, act, rot);

    scene->updateCamera();
    scene->updateScene();
}

void MainWindow::on_camera_top_clicked()
{
    const RotateOptions rot(M_PI / 36, 0, 0);
    const RotateX act;
    Transformation::transform(scene->camera, act, rot);

    scene->updateCamera();
    scene->updateScene();
}


void MainWindow::on_camera_bottom_clicked()
{
    const RotateOptions rot(-M_PI / 36, 0, 0);
    const RotateX act;
    Transformation::transform(scene->camera, act, rot);

    scene->updateCamera();
    scene->updateScene();
}

void MainWindow::on_camera_move_left_clicked()
{
    const MoveOptions mov(1, 0, 0);
    const Move act;
    Transformation::transform(scene->camera, act, mov);

    scene->updateCamera();
    scene->updateScene();
}

void MainWindow::on_camera_move_right_clicked()
{
    const MoveOptions mov(-1, 0, 0);
    const Move act;
    Transformation::transform(scene->camera, act, mov);

    scene->updateCamera();
    scene->updateScene();


}

void MainWindow::on_camera_move_down_clicked()
{
    const MoveOptions mov(0, -1, 0);
    const Move act;
    Transformation::transform(scene->camera, act, mov);

    scene->updateCamera();
    scene->updateScene();
}

void MainWindow::on_camera_move_up_clicked()
{
    const MoveOptions mov(0, 1, 0);
    const Move act;
    Transformation::transform(scene->camera, act, mov);

    scene->updateCamera();
    scene->updateScene();
}

void MainWindow::on_cam_scale_less_clicked()
{
    const ScaleOptions scale(0, 0, 0.5);
    const Scale act;
    Transformation::transform(scene->camera, act, scale);

    scene->updateCamera();
    scene->updateScene();
}


void MainWindow::on_cam_scale_higher_clicked()
{
    const ScaleOptions scale(0, 0, 2);
    const Scale act;
    Transformation::transform(scene->camera, act, scale);

    scene->updateCamera();
    scene->updateScene();
}

