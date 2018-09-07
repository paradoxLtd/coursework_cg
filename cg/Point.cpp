#include "Point.h"
#include <iostream>

void Point::init(double a, double b, double c, double d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

void Point::init(const Point& p)
{
	init(p.x, p.y, p.z, p.w);
}

void Point::create()
{
	init(0, 0, 0, 1);
}

Point::Point() // конструктор класса
{
	create();
}

Point::Point(double a, double b, double c, double d) // конструктор класса
{
	init(a, b, c, d);
}

/*
Point::Point(Options opt)
{
	init(opt[0], opt[1], opt[2], 1);
}
*/

Point::Point(Point *point) // конструктор класса
{
	init(*point);
}

// конструктор копирования
Point::Point(const Point &point)
{
	init(point);
}

Point::Point(Point &&point) noexcept
{
	init(point);
}

Point& Point::operator=(const Point& other) noexcept
{
	init(other);
	return *this;
}

Point& Point::operator=(Point&& other)noexcept
{
	init(other);
	return *this;
}

bool Point::isEqual(const Point &B)noexcept
{
	return((this->x == B.x) && (this->y == B.y) && (this->z == B.z));
}

bool Point::operator==(const Point& other)noexcept
{
	return isEqual(other);
}

bool Point::operator!=(const Point& other)noexcept
{
	return !isEqual(other);
}

double Point::localX() const noexcept
{
	return x;
}
double Point::localY() const noexcept
{
	return y;
}
double Point::localZ() const noexcept
{
	return z;
}
/*
double Point::worldX(Object f) const noexcept
{
	return x + f.center.x;
}

double Point::worldY(Object f) const noexcept
{
	return y + f.center.y;
}

double Point::worldZ(Object f) const noexcept
{
	return z + f.center.z;
}
*/
