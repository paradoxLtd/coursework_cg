#ifndef OBJECT_H
#define OBJECT_H

class Triangle;

#include "Triangle.h"
#include "Vector.h"
#include "Bit.h"

#include <cmath>
#include <vector>

// 754
//Состояния объектов
#define OBJECT_STATE_NULL 0x0000
#define OBJECT_STATE_ACTIVE 0x0001
#define OBJECT_STATE_VISIBLE 0x0002
#define OBJECT_STATE_CULLED 0x0004
#define OBJECT_STATE_ERROR 0x0008
// подробный вывод информации в std::cout
// нужен для дебага
#define OBJECT_DETAILED 0x0010 //16-ичная система же

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
    void create(std::vector<Point> vertex_local = {},
                std::vector<Point> texture_coords = {},
                Vector ux = Vector(1, 0, 0),
                Vector uy = Vector(0, 1, 0),
                Vector uz = Vector(0, 0, 1),
                Vector dir = Vector(1, 0, 0),
                Point center = Point(),
                int attr = 0,
               int state = OBJECT_STATE_NULL,
               const char *Name = "no name");

    // Спроецировать точку на плоскость xy
    //Point project(Point p)

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

    std::vector<Point> vertex_local; // список вершин с локальными координатами
    std::vector<Point> vertex_trans; // список вершин с преобразованными мировыми координатами

    // std::list<Point> normal;
    // std::list<Point> normal_trans;

    std::vector<Point> texture_coords;
    std::vector<Point> texture_coords_trans;

    std::vector<Triangle> polygons; // список полигонов

    static int get_id()
    {
        return next_id++;
    }

    Object(std::vector<Point> vertex_local = {},
            std::vector<Point> texture_coords = {},
            Vector ux = Vector(1, 0, 0),
            Vector uy = Vector(0, 1, 0),
            Vector uz = Vector(0, 0, 1),
            Vector dir = Vector(1, 0, 0),
            Point center = Point(),
            int attr = 0,
           int state = OBJECT_STATE_NULL,
           const char *Name = "no name");

    // Посчитать радиус и запомнить его в классе
    void updateRad();

    // Сбросить состояния всех полигонов
    void reset();

    // Приравнять резервный массив вершин к исходному
    void saveVertixes();

    // Приравнять резервный массив текстур к исходному
    void saveTextures();

    // Отсортировать вершины по\против часовой
    void sort();

    // Допустим объект задан пустым, так как было
    // неизвестно количество вершин и они динамически
    // добавились. Update обновит вектора-копии и
    // посчитает радиусы
    void update();

    std::vector<int> jarvis();

    friend std::ostream& operator<<(std::ostream& os,
                                    const Object& p);

    static void debug();

};

// разобраться, как упорядочивать и проверять упорядочивание через список вершин
// Предлагается через полярные координаты
// http://www.gamedev.ru/code/forum/?id=40728
// http://rsdn.org/forum/alg/3461405.hot

#endif // OBJECT_H
