#include "Triangle.h"
#include <iostream>

/*
void Triangle::copy(const Triangle& triangle)
{
	points = triangle.points;
}

void Triangle::destroy()
{
	points.clear();
}

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
{
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
}
*/
Triangle::Triangle(const Triangle &triangle)
{
	copy(triangle);
}

Triangle::~Triangle()
{
	destroy();
}

Triangle& Triangle::operator=(const Triangle& other) noexcept
{
	destroy();
	copy(other);
	return *this;
}

Triangle& Triangle::operator=(Triangle&& other)noexcept
{
	destroy();
	copy(other);
	other.destroy();
	return *this;
}

/*
bool Triangle::isEqual(
	const Triangle &O) noexcept
{
	if (points.size == O.points.size)
	{
		for (Point p1 : points; )
		{

		}
	}
	return 0;
	return ((this->A == O.A) && (this->B == O.B) && (this->C == O.C));
}

bool Triangle::operator==(const Triangle& other)noexcept
{
	return isEqual(other);
}

bool Triangle::operator!=(const Triangle& other)noexcept
{
	return !isEqual(other);
}
*/
