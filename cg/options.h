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
    void init(double a = 0,
              double b = 0,
              double c = 0,
              bool inv = false);
public:
    bool inverse;
    Options(double a = 0,
            double b = 0,
            double c = 0,
            bool inv = false)
    {
        init(a, b, c, inv);
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
    MoveOptions(double dx = 0,
                double dy = 0,
                double dz = 0,
                bool inv = false);

    // Для корректной работы ObjectList.cameraTransformation
    MoveOptions(const Point *p, bool inv = false);

    friend std::ostream& operator<<(std::ostream& os,
                                    const MoveOptions& p);
};

/*
param[0/1/2] - коэффициент масштабирования x/y/z
*/
class ScaleOptions : public Options
{
public:
    ScaleOptions(double kx = 1,
                 double ky = 1,
                 double kz = 1,
                 bool inv = false);

    friend std::ostream& operator<<(std::ostream& os,
                                    const ScaleOptions& p);
};


/*
param[0] - выбор оси, x/y/z
param[1] - угол поворота
*/
struct RotateOptions : public Options
{
public:
    RotateOptions(double dx = 0,
                 double dy = 0,
                 double dz = 0,
                 bool inv = false);

    friend std::ostream& operator<<(std::ostream& os,
                                    const RotateOptions& p);
};

#endif // OPTIONS_H
