#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <list>
#include <QColor>

class Point;

#include "Point.h"
#include "Object.h"

class Triangle
{
private:

	void copy(const Triangle& triangle) noexcept;

	void destroy() noexcept;

public:
	//std::list<Point> points;

	Object *object; // указатель на список вершин
	int indexes[3]; // 3 индекса для выбора 3-ех точек

	int state; // состояние полигона - активный, отсеченный и т.д.
	int attr; // физические свойства - представляет из себя ряд флагов, таких как прозрачность, способность отражать цвет
    QColor color; // цвет

	/*Конструкторы */
	Triangle(Object* ob, int i1, int i2, int i3)
	{
		object = ob;
		indexes[0] = i1;
		indexes[1] = i2;
		indexes[2] = i3;
	}

    Triangle(Object* obj, int i1, int i2, int i3,
                       int st, int a, QColor col);

	Triangle(const Triangle &triangle);
	~Triangle();

	Triangle& operator=(const Triangle& other) noexcept;

	Triangle& operator=(Triangle&& other)noexcept;

	bool isEqual(const Triangle &B)noexcept;

	bool operator==(const Triangle &B)noexcept;

	bool operator!=(const Triangle &B)noexcept;
};

#endif

