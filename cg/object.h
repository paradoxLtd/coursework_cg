#ifndef OBJECT_H
#define OBJECT_H

class Triangle;

#include "triangle.h"
#include "vector.h"
#include "bit.h"

#include <cmath>

// 754
//Состояния объектов
#define OBJECT_STATE_NULL 0x0000
#define OBJECT_STATE_ACTIVE 0x0001
#define OBJECT_STATE_VISIBLE 0x0002
#define OBJECT_STATE_CULLED 0x0004

// Текстуры
// Однокаркасный
#define OBJECT_SINGLE_FRAME 0x0001
// Многокаркасный объект для поддержки формата .md2
#define OBJECT_MULTIPLE_FRAME 0x0002
// Объект, содержащий многоугольники с текстурой
#define OBJECT_TEXTURE  0x0004

class Object
{
private:

public:
    // 478
    int id; //Числовой идентификатор объекта
    const char *name;
    static int next_id; // айди следующего элемента
    int state; // Состояние объекта
    int attr; // Атрибуты объекта

    double avg_radius; // Средний радиус объекта для обнаружения столкновений
    double max_radius; // Максимальный радиус объекта

    Point center; // Положение объекта в мировых координатах
    Vector dir; // Единичный вектор направления
    Vector ux, uy, uz;
    // Локальные оси для отслеживания ориентации объекта (обновляются
    // автоматически при вызове функции поворота)

    std::list<Point> vertex_local; // список вершин с локальными координатами
    std::list<Point> vertex_trans; // список вершин с преобразованными мировыми координатами
    int vertices_size; // размер списков

    // std::list<Point> normal;
    // std::list<Point> normal_trans;

    std::list<Point> texture_coords;
    std::list<Point> texture_coords_trans;

    std::list<Triangle> polygons; // список полигонов
    int polygons_size; // количество полигонов

    static int get_id()
    {
        return next_id++;
    }

    Object();

    void updateRad();

    void reset();

};

// разобраться, как упорядочивать и проверять упорядочивание через список вершин
// Предлагается через полярные координаты
// http://www.gamedev.ru/code/forum/?id=40728
// http://rsdn.org/forum/alg/3461405.hot

#endif // OBJECT_H
