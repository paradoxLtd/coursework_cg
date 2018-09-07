#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <list>
#include <QColor>

class Object;

#include "Point.h"
#include "Object.h"

// 754
//Состояния объектов
#define POLYNOM_STATE_NULL 0x0000
#define POLYNOM_STATE_ACTIVE 0x0001
#define POLYNOM_STATE_CLIPPED 0x0002
#define POLYNOM_STATE_BACKFACE 0x0004

#define POLYNOM_ATTR_2SIDED 0x0001
#define POLYNOM_ATTR_TRANSPARENT 0x0002
#define POLYNOM_ATTR_8BITCOLOR 0x0004
#define POLYNOM_ATTR_RGB16 0x0008
#define POLYNOM_ATTR_RGB24 0x0010

#define POLYNOM_SHADE_MODE_PURE 0x0020
#define POLYNOM_SHADE_MODE_CONSTANT 0x0020
#define POLYNOM_SHADE_MODE_FLAT 0x0040
#define POLYNOM_SHADE_MODE_GOURAUD 0x0080
#define POLYNOM_SHADE_MODE_PHONG 0x0100
#define POLYNOM_SHADE_MODE_FASTPHONG 0x0100
#define POLYNOM_SHADE_MODE_TEXTURE 0x0200

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

