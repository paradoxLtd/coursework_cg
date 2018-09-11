#ifndef OPTIONS_H
#define OPTIONS_H

class Point;

#include <iostream>

#include "Point.h"
#include "Vector.h"

#define AXIS_X 101
#define AXIS_Y 102
#define AXIS_Z 103
#define NOTHING 0

class Options
{
public:
    double params[3];
    bool inverse;
    Options() {}
    Options(double a, double b, double c)
    {
        params[0] = a;
        params[1] = b;
        params[2] = c;
        inverse = false;
    }

    double& operator[] (int index)
    {
        if (index > 2)
        {
            std::cout << "Класс Options не допускает обращение к элементу массива параметров с индексом больше 2 ";
            return params[2];
        }
        return params[index];
    }
};

/*
param[0/1/2] - сдвиг по x/y/z
*/
class MoveOptions : public Options
{
public:
    MoveOptions();

    MoveOptions(double dx, double dy, double dz,
                bool inv = false);

    MoveOptions(Point *p, bool inv = false);

    // Для корректной работы ObjectList.cameraTransformation
    MoveOptions(const Point *p, bool inv = false);
};

/*
param[0/1/2] - коэффициент масштабирования x/y/z
*/
class ScaleOptions : public Options
{
public:
    ScaleOptions();
};


/*
param[0] - выбор оси, x/y/z
param[1] - угол поворота
*/
struct RotateOptions : public Options
{
public:
    RotateOptions();
    RotateOptions(int choose, double angle, bool in = false);
};

#endif // OPTIONS_H
