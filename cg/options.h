#ifndef OPTIONS_H
#define OPTIONS_H

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
    Options() {};
    Options(double a, double b, double c)
    {
        params[0] = a;
        params[1] = b;
        params[2] = c;
        inverse = false;
    };

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
    MoveOptions()
    {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
        inverse = false;
    }

    MoveOptions(Point p)
    {
        params[0] = p.x;
        params[1] = p.y;
        params[2] = p.z;
        inverse = false;
    }
    MoveOptions(Point p, bool in)
    {
        params[0] = p.x;
        params[1] = p.y;
        params[2] = p.z;
        inverse = in;
    }
};

class ScaleOptions : public Options
{
public:
    ScaleOptions()
    {
        params[0] = 1;
        params[1] = 1;
        params[2] = 1;
        inverse = false;
    }
};
/*
param[0/1/2] - коэффициент масштабирования x/y/z
*/


struct RotateOptions : public Options
{
public:
    RotateOptions()
    {
        params[0] = NOTHING;
        params[1] = 0;
        params[2] = 0;
        inverse = false;
    }
    RotateOptions(int choose, double angle, bool in = false)
    {
        params[2] = 0;
        params[1] = angle;
        params[0] = NOTHING;
        switch (choose)
        {
        case AXIS_X:
        {
            params[0] = AXIS_X;
            break;
        }
        case AXIS_Y:
        {
            params[0] = AXIS_Y;
            break;
        }
        case AXIS_Z:
        {
            params[0] = AXIS_Z;
            break;
        }
        default:
            std::cout << "Указана несуществующая ось поворота" << choose;
            params[1] = 0;
        }
        inverse = in;
    }
};
/*
param[0] - выбор оси, x/y/z
param[1] - угол поворота
*/

#endif
