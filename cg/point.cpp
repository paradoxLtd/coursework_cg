#include "Point.h"
#include <iostream>

void Point::init(double a, double b, double c, double d)
{
    x = a;
    y = b;
    z = c;
    w = d;
    name = "Point";
}

void Point::init(const Point& p)
{
    init(p.x, p.y, p.z, p.w);
}

void Point::create()
{
    init(0, 0, 0, 1);
}

// конструктор класса
Point::Point(double x, double y,
             double z, double w)
{
    init(x, y, z, w);
}

Point::Point(Options opt)
{
    init(opt[0], opt[1], opt[2], 1);
}

// конструктор класса
Point::Point(Point *point)
{
    init(*point);
}

// конструктор копирования
Point::Point(const Point &point)
{
    init(point);
}

// конструктор переопределения
Point::Point(Point &&point) noexcept
{
    init(point);
}

// Переопределение = для копирования
Point& Point::operator=
(const Point& other) noexcept
{
    init(other);
    return *this;
}

// Переопределение = для перемещения
Point& Point::operator=
(Point&& other) noexcept
{
    init(other);
    return *this;
}

// Сравнение точек
bool Point::isEqual(const Point &B)
noexcept
{
    return(
                (fabs (this->x - B.x) > 0.0001)
                &&
                (fabs(this->y - B.y) > 0.0001)
                &&
                (fabs(this->z - B.z) > 0.0001)
                );
}

// Переопределение оператора ==
bool Point::operator==
(const Point& other)noexcept
{
    return isEqual(other);
}

// Переопределение оператора !=
bool Point::operator!=
(const Point& other)noexcept
{
    return !isEqual(other);
}

// Переопределение +
Point &Point::operator +(Point &p)
{
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;

    return  *this;
}

// Переопределение +=
Point &Point::operator+=(Point &p)
{
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;

    return  *this;
}

// переопределение вывода
std::ostream& operator<<
(std::ostream& os, const Point& p)
{
     os << "\n" << p.name <<
           "(x: " << p.x <<
           ", y: " << p.y <<
           ", z: " << p.z <<
           ", w: " << p.w <<
           ")";
    return os;
}
