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
     target = RenderContext(ui->widget, WIDTH_WIN, HEIGHT_WIN);

    //image2 = new QImage(QImage::Format_RGB32);


    texture = Texture(QImage(QDir::currentPath().append("/objs/bricks.jpg")));
    mesh = Mesh(QDir::currentPath().append("/objs/cube.obj").toStdString());
    trans = Transform(Vector4f(0,0.0f,3.0f));

    camera = Camera( Matrix4f().InitPerspective(
                         toRadians(70.0f),
                         target.GetWidth()/ target.GetHeight(),
                         0.1f, 1000.0f));

    /*
    std::cout << "lol\n";
    std::cout << "x:" << camera.GetTransform().GetRot().GetX() <<
                 "y:" << camera.GetTransform().GetRot().GetY() <<
                 "z:" << camera.GetTransform().GetRot().GetZ() <<
                 "w:" << camera.GetTransform().GetRot().GetW();
    */

    /*Camera camera = Camera( Matrix4f().InitOrthographic(0,
                    600, 0, 1000.0f));*/


    std::vector <std::vector <float>> proj = Matrix4f().InitPerspective(toRadians(70.0f),
                                                                        target.GetWidth()/ target.GetHeight(), 0.1f, 1000.0f).GetMtx();


    Matrix4f vp = camera.GetViewProjection();
    /*for (auto row: vp.GetMtx()) {
        for (auto c: row) {
            std::cout << c << " ";
        }
        std::cout << "\n";
    }*/

    //target.Clear((byte)0x00);
    target.ClearDepthBuffer();

    mesh.Draw(target, vp, trans.GetTransformation(), texture);

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

void MainWindow::on_camera_left_clicked()
{
    const float movAmt = 1.0f;
    camera.Move(camera.GetTransform().GetRot().GetLeft(), movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);

}

void MainWindow::on_camera_top_clicked()
{
    const float movAmt = 1.0f;
    camera.Move(camera.GetTransform().GetRot().GetForward(), movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}

void MainWindow::on_camera_bottom_clicked()
{
    const float movAmt = 1.0f;
    camera.Move(camera.GetTransform().GetRot().GetForward(), -movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}


void MainWindow::on_camera_right_clicked()
{
    const float movAmt = 1.0f;
    camera.Move(camera.GetTransform().GetRot().GetRight(), movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}

void MainWindow::on_camera_move_right_clicked()
{
    const float movAmt = 0.1f;
    camera.Rotate(Camera::Y_AXIS, -movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);

}

void MainWindow::on_camera_move_up_clicked()
{
    const float movAmt = 0.1f;
    camera.Rotate(camera.GetTransform().GetRot().GetRight(), movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    const float movAmt = 0.2f;

    switch (e->key()) {
    case Qt::Key_W:
        camera.Move(camera.GetTransform().GetRot().
                    GetForward(), movAmt);
        break;
    case Qt::Key_S:
        camera.Move(camera.GetTransform().GetRot().
                    GetForward(), -movAmt);
        break;
    case Qt::Key_A:
        camera.Move(camera.GetTransform().GetRot().
                    GetLeft(), movAmt);
        break;
    case Qt::Key_D:
        camera.Move(camera.GetTransform().GetRot().
                    GetRight(), movAmt);
        break;
    case Qt::Key_I:
        camera.Rotate(camera.GetTransform().GetRot().
                      GetRight(), movAmt);
        break;
    case Qt::Key_J:
        camera.Rotate(Camera::Y_AXIS, movAmt);
        break;
    case Qt::Key_K:
        camera.Move(camera.GetTransform().GetRot().
                    GetForward(), -movAmt);
        break;
    case Qt::Key_L:
         camera.Rotate(Camera::Y_AXIS, -movAmt);
        break;
    }
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}

void MainWindow::on_camera_move_left_clicked()
{
    const float movAmt = 0.1f;
    camera.Rotate(Camera::Y_AXIS, movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}

void MainWindow::on_camera_move_down_clicked()
{
    const float movAmt = 0.1f;
    camera.Rotate(camera.GetTransform().GetRot().GetRight(), -movAmt);
    target.ClearDepthBuffer();
    image->fill(Qt::white);
    ui->widget->setImage(*image);
    Matrix4f vp = camera.GetViewProjection();
    mesh.Draw(target, vp, trans.GetTransformation(), texture);
}
