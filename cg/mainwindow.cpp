#include "mainwindow.h"
#include <qDebug>
#include "ui_mainwindow.h"
#include "drawer.h"
#include "point.h"
#include "vector.h"
#include "Scene.h"
#include "camera.h"
#include "triangle.h"
#include "objectlist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->graphics_scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setSceneRect(0, 0, 600, 600);
    ui->graphicsView->setScene(this->graphics_scene);
    ui->graphicsView->setMinimumSize(600, 600);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->installEventFilter(this);

}

void MainWindow::on_pushButton_clicked()
{
    Point cam_pos(-100, -100, -100,1);
    Vector cam_dir(0,0,0);
    Vector vscale(0.5,0.5,0.5);
    Vector vpos(0,0,0);
    Vector vrot(0,0,0);

    Point p1(0,50,0,1);
    Point p2(50,-50,0,1);
    Point p3(-50,-50,0,1);

    std::vector<Point> vertex{p1,p2,p3};
    Object new_obj(vertex);
    qDebug()  << new_obj.vertex_local[0].x;

    Indexes v(1,2,3);
    Indexes vt(1,2,3);

    Triangle tr(&new_obj,v,vt);
    new_obj.pushPolygon(tr);

    /*Point poly_pos(0,0,100,1);
    new_obj.state = POLY4DV2_STATE_ACTIVE;
    new_obj.attr = 0;
    new_obj*/

    /*
    ObjectList obj_list;
    obj_list.objects.push_back(new_obj);
    obj_list.localToWorld();
    obj_list.worldToCam(cam);
    obj_list.camToAxonometricAndScreenObject(cam);

    Drawer dr(this->graphics_scene);
    dr.draw_object(new_obj);
    */


    Scene scene(this->graphics_scene);
    scene.pushObject(new_obj);
    scene.updateCamera();
    scene.draw();


    //Drawer dr(this->graphics_scene);
    //ObjectList objs;
    //objs.push(new_obj);
    //dr.draw_objects(objs);

    //QPen mypen(Qt::black);
    //this->graphics_scene->addLine(0, 0, 600, 600, mypen);
}


MainWindow::~MainWindow()
{
    delete ui;
}
