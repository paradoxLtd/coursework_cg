#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window_size.h"
#include "texture.h"
#include "mesh.h"
#include "transform.h"
#include "camera.h"
#include <cmath>

#include <QDebug>

float toRadians(float angle)
{
    return M_PI * angle / 180.;
}

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

    //qDebug() << QDir::currentPath().append("/objs/cube.obj");

    //Display display = new Display(800, 600, "Software Rendering");
    RenderContext target(ui->widget, WIDTH_WIN, HEIGHT_WIN);

    //image2 = new QImage(QImage::Format_RGB32);


    Texture texture(QImage(QDir::currentPath().append("/objs/bricks.jpg")));
    Mesh monkeyMesh = Mesh(QDir::currentPath().append("/objs/smoothMonkey0.obj").toStdString());
    Transform monkeyTransform = Transform(Vector4f(0,0.0f,3.0f));

    Camera camera = Camera( Matrix4f().InitPerspective(toRadians(70.0f),
                    target.GetWidth()/ target.GetHeight(), 0.1f, 1000.0f));

    /*Camera camera = Camera( Matrix4f().InitOrthographic(0,
                    600, 0, 1000.0f));*/


    std::vector <std::vector <float>> proj = Matrix4f().InitPerspective(toRadians(70.0f),
                                                                        target.GetWidth()/ target.GetHeight(), 0.1f, 1000.0f).GetMtx();

    for (auto row: proj) {
        for (auto c: row) {
            std::cout << c << " ";
        }
        std::cout << "\n";
    }

    Matrix4f vp = camera.GetViewProjection();


    monkeyMesh.Draw(target, vp, monkeyTransform.GetTransformation(), texture);

    //float rotCounter = 0.0f;
    //long previousTime = System.nanoTime();
    /*while(true)
    {
        long currentTime = System.nanoTime();
        float delta = (float)((currentTime - previousTime)/1000000000.0);
        previousTime = currentTime;

        camera.Update(display.GetInput(), delta);
        Matrix4f vp = camera.GetViewProjection();

        monkeyTransform = monkeyTransform.Rotate(new Quaternion(new Vector4f(0,1,0), delta));

        target.Clear((byte)0x00);
        target.ClearDepthBuffer();
        monkeyMesh.Draw(target, vp, monkeyTransform.GetTransformation(), texture2);
        terrainMesh.Draw(target, vp, terrainTransform.GetTransformation(), texture);

        display.SwapBuffers();
    }*/


}

MainWindow::~MainWindow()
{
    delete ui;
}

//Загрузить
void MainWindow::on_pushButton_clicked()
{

}
