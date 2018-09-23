#ifndef PLANE_H
#define PLANE_H

#include "point.h"
#include "vector.h"
#include <cmath>

class Plane
{
public:
    Plane()
    {

    };
    Plane(Point &point, Vector &n, bool normalize);
    Plane(const Plane &p);

    Plane(Plane &&p);

    Plane& operator=(const Plane& other);

    Plane& operator=(Plane&& other);

    ~Plane() = default;

    double compute_point_in_plane(Point point);
    //int intersect_param_line_plane() Функция для определения пересечения
    //параметрической прямой и плоскости

private:
    Point p;
    Vector n;
    bool normalize;
};

#endif // PLANE_H
