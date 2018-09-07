#ifndef TRIANGLE_LIST_H
#define TRIANGLE_LIST_H

#include <list>
#include <QColor>

#include "Point.h"
#include "Object.h"

// ѕеред отсечени€ми сливаем все многоугольники в общий котел
class TriangleInList
{
public:
	Point list_original[3]; // список вершин до преобразовани€
	Point list_changed[3]; // список вершин после преобразовани€

	int state; // состо€ние полигона - активный, отсеченный и т.д.
	int attr; // физические свойства - представл€ет из себ€ р€д флагов, таких как прозрачность, способность отражать цвет
    QColor color; // цвет

	TriangleInList *next;
	TriangleInList *prev;

				 /* онструкторы */
	TriangleInList(const Point &p1, const Point &p2, const Point &p3);
	TriangleInList(const Triangle &triangle);
	~TriangleInList();

	TriangleInList& operator=(const TriangleInList& other) noexcept;

	TriangleInList& operator=(TriangleInList&& other)noexcept;

	bool isEqual(const TriangleInList &B)noexcept;

	bool operator==(const TriangleInList &B)noexcept;

	bool operator!=(const TriangleInList &B)noexcept;
};

#define ARR_SIZE 1000

class RenderList
{
public:
	int state; // состо€ние списка визуализации
	int attr; //  атрибуты списка
	TriangleInList* ptrs[ARR_SIZE]; //список визуализации
	// содержит ссылки на автономную визуализируемую поверхность

	TriangleInList data[ARR_SIZE]; // реальные данные о многоугольниках
	int size; // количество многоугольников
	void reset()
	{
		size = 0;
	}
};

#endif
