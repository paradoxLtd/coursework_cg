#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "scene.h"
#include "bitmap.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Scene *scene;
    QTimer *tmr;

private slots:
    void on_pushButton_clicked();

    void on_camera_left_clicked();

    void on_camera_right_clicked();

    void on_camera_top_clicked();

    void on_camera_bottom_clicked();

    void on_camera_move_left_clicked();

    void on_camera_move_right_clicked();

    void on_camera_move_down_clicked();

    void on_camera_move_up_clicked();

    void on_cam_scale_less_clicked();

    void on_cam_scale_higher_clicked();

private:
    QGraphicsScene* graphics_scene;
    QImage *image;
    Bitmap *bmap;
    Ui::MainWindow *ui;
private slots:
    void rot_fig_timer();

};

#endif // MAINWINDOW_H
