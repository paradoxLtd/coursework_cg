#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <list>
#include <QColor>
#include <iostream>
#include <vector>

class Object;

#include "indexes.h"
#include "Point.h"
#include "Object.h"
#include "errors.h"

// 754
//Состояния объектов
#define POLYGON_STATE_NULL 0x0000
#define POLYGON_STATE_ACTIVE 0x0001
#define POLYGON_STATE_CLIPPED 0x0002
#define POLYGON_STATE_BACKFACE 0x0004

#define POLYGON_ATTR_NULL 0x0000
#define POLYGON_ATTR_2SIDED 0x0001
#define POLYGON_ATTR_TRANSPARENT 0x0002
#define POLYGON_ATTR_8BITCOLOR 0x0004
#define POLYGON_ATTR_RGB16 0x0008
#define POLYGON_ATTR_RGB24 0x0010

#define POLYGON_SHADE_MODE_PURE 0x0020
#define POLYGON_SHADE_MODE_CONSTANT 0x0020
#define POLYGON_SHADE_MODE_FLAT 0x0040
#define POLYGON_SHADE_MODE_GOURAUD 0x0080
#define POLYGON_SHADE_MODE_PHONG 0x0100
#define POLYGON_SHADE_MODE_FASTPHONG 0x0100
#define POLYGON_SHADE_MODE_TEXTURE 0x0200

// Прошло проверки, 11.09.18 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// изменено - отдебажить std::Vector<Point> getPoints();
class Triangle
{
private:

    void copy(const Triangle& triangle) noexcept;

    void destroy() noexcept;

    // Определение нормали, не для внешнего использования
    // Используйте один из двух публичных методов
    Vector getNormal(std::vector<Point> vertix) const noexcept;

public:
    Object *object; // указатель на объект

    Indexes indexes_vert; // индексы вершин
    Indexes indexes_text; // индексы текстур
    //Indexes indexes_norm; // индексы вершин

    Vector normal;

    int state; // состояние полигона - активный, отсеченный и т.д.
    int attr; // физические свойства - представляет из себя ряд флагов, таких как прозрачность, способность отражать цвет
    QColor color; // цвет

    /*Конструкторы */

    Triangle(Object* ob, Indexes v,
             Indexes vt, /*Indexes &vn,*/
             int st = POLYGON_STATE_ACTIVE,
             int attr = POLYGON_ATTR_NULL,
             QColor color = Qt::white);

    Triangle(const Triangle &triangle);
    ~Triangle();

    Triangle& operator=(const Triangle& other) noexcept;

    Triangle& operator=(Triangle&& other)noexcept;

    bool isEqual(const Triangle &B)noexcept;

    bool operator==(const Triangle &B)noexcept;

    bool operator!=(const Triangle &B)noexcept;

    // нормаль для измененного полигона(после преобразо
    // ваний из одних координат в другие)
    Vector normalTrans() const noexcept;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Triangle& p);
    // Получить массив точек
    std::vector<Point> getPoints();

    static void debug();
};

#endif // TRIANGLE_H
