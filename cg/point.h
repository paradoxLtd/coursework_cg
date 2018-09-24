#ifndef POINT_H
#define POINT_H

class Options;

#include "Resource.h"
#include "Options.h"

#define NO_POINT 0

// Прошло проверки, не изменялось, 09.09.18
class Point
{
    void create();
    void init(double a, double b, double c, double d);
    void init(const Point &p);
public:
    double x, y, z, w;
    std::string name; //для дебагинга

    /*Конструкторы */

    Point(Point *p);
    Point(const Point &point);
    Point(double x = 0, double y = 0,
          double z = 0, double w = 1);

    Point(Options opt);

    Point(Point &&point) noexcept;

    Point& operator=
    (const Point& other)noexcept;

    Point& operator=
    (Point&& other)noexcept;

    bool isEqual(const Point &B)noexcept;

    bool operator==
    (const Point& other)noexcept;

    bool operator!=
    (const Point& other)noexcept;

    Point & operator+
    (Point &other);

    Point & operator+=
    (Point &other);

    friend std::ostream& operator<<
    (std::ostream& os, const Point& p);

    static void debug();
};

#endif // POINT_H
