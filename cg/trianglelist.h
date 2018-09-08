#ifndef TRIANGLELIST_H
#define TRIANGLELIST_H

#include <list>
#include <QColor>

#include "Point.h"
#include "Object.h"

// Перед отсечениями сливаем все многоугольники в общий котел
class TriangleInList
{
public:
    Point list_original[3]; // список вершин до преобразования
    Point list_changed[3]; // список вершин после преобразования

    int state; // состояние полигона - активный, отсеченный и т.д.
    int attr; // физические свойства - представляет из себя ряд флагов, таких как прозрачность, способность отражать цвет
    QColor color; // цвет

    TriangleInList *next;
    TriangleInList *prev;

                 /*Конструкторы */
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
    int state; // состояние списка визуализации
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

#endif // TRIANGLELIST_H
