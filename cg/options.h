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
protected:
    double params[3];
public:
    bool inverse;
    Options(double a = 0,
            double b = 0,
            double c = 0)
    {
        params[0] = a;
        params[1] = b;
        params[2] = c;
        inverse = false;
    }

    // для чтения
    const double& operator[] (int index) const
    {
        if (index > 2)
        {
            std::cout << "Класс Options не допускает"
                      << " обращение к элементу массива" <<
                         " параметров с индексом больше 2 ";
            return params[2];
        }
        return params[index];
    }

    // для записи
    void set (double meaning, int index)
    {
        if (index > 2)
        {
            std::cout << "Класс Options не допускает"
                      << " обращение к элементу массива" <<
                         " параметров с индексом больше 2 ";
        }
        else
        {
            params[index] = meaning;
        }
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
