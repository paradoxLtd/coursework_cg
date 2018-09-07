#ifndef CAMERA_H
#define CAMERA_H
#include "Point.h"

class Camera
{
public:
    Point point;
	// Направление обзора 431
	double ang_x, ang_y, ang_z;

	double fov; // field_of_view поле обзора
};

#endif
