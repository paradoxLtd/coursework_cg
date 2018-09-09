#ifndef CAMERA_H
#define CAMERA_H

class Point;

#include "point.h"
#include "vector.h"
#include "transformation.h"
#include "plane.h"
#include <cmath>

#define VIEWPLANE_WIDTH 2.0
#define FOV 90.0

/*Используется камера типа UVN подробнее о ней с551*/
class Camera
{
public:
    Camera() = default;
    Camera(int attr, Point &position, Vector &u, Vector &v, Vector &n,
           Point &target, double n_plane, double f_plane,
           double viewp_w, double viewp_h);

    Camera(const Camera &c);
    //Camera(Camera &&c);

    Camera & operator = (const Camera &c);
    //Camera operator = (Camera &&c);

    void build_cam_matrix();

    double viewplane_width, viewplane_height;
    double dst;
    double near_plane, far_plane; // Ближняяи дальние плоскости отсечения
    Point position; //Положение камеры в мировых координатах

private:
    int state; //Состояние камеры
    int attr; //атрибутыкамеры

    Vector u, v, n; //Вектора, на которых основана UVN модель камеры
    Point target; // Точка, на которую смотрит камера в модели UVN
    double view_dst_hor, view_dst_ver;// расстояния по горизонтали и вертикали,
                                     //используемые при аксонометрическом преобразовании.
    double fov; //Field of View, как правило это pi/2 (90 гр), для дальнейшего
                //простого отсечения

    Plane left_plane, right_plane, top_plane, bottom_plane;

    double viewport_w, viewport_h, viewport_xc, viewport_yc;
    double asp_ratio;

    Matrix mcam; //матрица перехода из коор-т матрицы в координаты камеры
    Matrix mper; //из камеры в аксонометрические
    Matrix mscr; //изаксонометрических в экранные

    void _copy(const Camera &c);

    void _init(int attr, Point &position, Vector &u, Vector &v, Vector &n,
               Point &target, double n_plane, double f_plane,
               double viewp_w, double viewp_h);
};

#endif

