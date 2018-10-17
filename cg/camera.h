#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "options.h"
#include "plane.h"
#include "matrix.h"
#include <cmath>

#define VIEWPLANE_WIDTH 600.0
#define FOV 90.0

/*Используется камера типа UVN подробнее о ней с551*/
class Camera
{
public:
    Camera(int attr = 0,
           Point position = Point(0,0,0,1),
           Point target = Point(0,0,1,1),
           double n_plane = 400,
           double f_plane = 600,
           double viewp_w = 600,
           double viewp_h = 600);

    Camera(const Camera &c);
    Camera(Camera &&c);

    Camera & operator = (const Camera &c);
    Camera & operator = (Camera &&c);

    void build_cam_matrix();

    //Из-за чего тут произошла путаница, параметры viewplane_width и viewplane_height
    //могут быть нормированными, а могут соответствовать размерам экрана
    //отсюда и dst тоже тоже может быть как нормированным, так и нет
    //если они нормированны, то здесь то и нужны view_dst_hor, чтобы в аксонометрии работать
    //с фактическим размером

    //что мы делаем, viewplane_width соответствуют размерам экрана, поэтому
    //view_dst_hor и view_dst_ver убираются, далее, с учетом того, что у нас fov = 90 гр, то
    //начальный dst будет равен 1/2 viewplane_width.
    double viewplane_width, viewplane_height; // ширина и высота области, на которую производится
                                                                        // проецирование

    double dst;
    // Ближняяи дальние плоскости отсечения
    double near_plane, far_plane;
    // Положение камеры в мировых координатах
    Point position;
    // расстояния по горизонтали и вертикали,
    // используемые при аксонометрическом
    // преобразовании
    //double view_dst_hor, view_dst_ver;

    double asp_ratio;
    int state; //Состояние камеры
    int attr; //атрибуты камеры

    //Вектора, на которых основана UVN модель
    //камеры
    Vector u, v, n;
    // Точка, на которую смотрит камера в модели UVN
    Point target;

    //Field of View, как правило это pi/2 (90 гр)
    //, для дальнейшего простого отсечения
    double fov;

    //Эти плоскости по сути нафиг не нужны
    Plane left_plane, right_plane;
    Plane top_plane, bottom_plane;

    double viewport_w, viewport_h;
    double viewport_xc, viewport_yc;

    Matrix mcam; //матрица перехода из коор-т матрицы в координаты камеры
    Matrix mper; //из камеры в аксонометрические
    Matrix mscr; //из аксонометрических в экранные

    static void debug();

    friend std::ostream& operator<<
    (std::ostream& os, const Camera& p);

private:
    void _copy(const Camera &c);

    void _init(int attr, Point &position,
               Vector &u, Vector &v, Vector &n,
               Point &target, double n_plane,
               double f_plane,
               double viewp_w,
               double viewp_h);
};


#endif // CAMERA_H
