#include "Triangle.h"
#include <iostream>


void Triangle::copy(const Triangle& triangle) noexcept
{

    this->object = triangle.object; // указатель на список вершин
    this-> indexes[0] = triangle.indexes[0]; // 3 индекса для выбора 3-ех точек
    this->indexes[1] = triangle.indexes[1];
    this->indexes[2] = triangle.indexes[2];
    this->state = triangle.state; // состояние полигона - активный, отсеченный и т.д.
    this->attr = triangle.attr; // физические свойства - представляет из себя ряд флагов, таких как прозрачность, способность отражать цвет
    this->color = triangle.color; // цвет
}

void Triangle::destroy() noexcept
{
    object = nullptr;
}

Triangle::Triangle(Object* obj, int i1, int i2, int i3,
                   int st, int a, QColor col)
{
    this->object = obj; // указатель на список вершин
    this->indexes[0] = i1; // 3 индекса для выбора 3-ех точек
    this->indexes[1] = i2;
    this->indexes[2] = i3;
    this->state = st; // состояние полигона - активный, отсеченный и т.д.
    this->attr = a; // физические свойства - представляет из себя ряд флагов, таких как прозрачность, способность отражать цвет
    this->color = col; // цвет
}

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
