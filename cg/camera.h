#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera
{
public:
    Point point;
    // Направление обзора 431
    double ang_x, ang_y, ang_z;
    double far_clip_z, near_clip_z;
    double viewplane_width, viewplane_height;
    double view_dist;

    double fov; // field_of_view поле обзора
};


#endif // CAMERA_H
