#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "bitmap.h"
#include "camera.h"
#include "transform.h"
#include "rendercontext.h"
#include "mesh.h"
#include <QTimer>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_camera_left_clicked();

    void on_camera_top_clicked();

    void on_camera_bottom_clicked();

    void on_camera_right_clicked();

    void on_camera_move_up_clicked();

    void on_camera_move_right_clicked();

    void on_camera_move_down_clicked();

    void on_camera_move_left_clicked();

    void keyPressEvent(QKeyEvent *e);

private:
    QGraphicsScene* graphics_scene;
    QImage *image, *image2;
    Bitmap bmap;
    Ui::MainWindow *ui;

    Camera camera;
    RenderContext target;
    Mesh mesh;
    Texture texture;
    Transform trans;
};

#endif // MAINWINDOW_H
