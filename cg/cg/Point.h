#ifndef POINT_H
#define POINT_H

//#include "Resource.h"
//#include "Object.h"
//#include "Options.h"

//#define NO_POINT 0

class Point
{
	void create();
	void init(double a, double b, double c, double d);
	void init(const Point &p);
public:
	double x, y, z, w;

	/*Конструкторы */
	Point();

	Point(Point *p);
	Point(const Point &point);
	Point(double a, double b, double c, double d);
    Point(Options& ds);

	double localX() const noexcept;
	double localY() const noexcept;
	double localZ() const noexcept;

	double worldX(Object f) const noexcept;
	double worldY(Object f) const noexcept;
	double worldZ(Object f) const noexcept;

	Point(Point &&point) noexcept;

	Point& operator=(const Point& other) noexcept;

	Point& operator=(Point&& other)noexcept;

	bool isEqual(const Point &B)noexcept;

	bool operator==(const Point& other)noexcept;

	bool operator!=(const Point& other)noexcept;
};

#endif
