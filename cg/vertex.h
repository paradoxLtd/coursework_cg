#ifndef VERTEX_H
#define VERTEX_H

#include "point.h"

class Vertex : public Point
{
public:
    Vertex(Vertex *p) : Point(p) { v_color = p->v_color; }
    Vertex(const Vertex &point) : Point(point) { v_color = point.v_color; }
    Vertex(double x = 0, double y = 0,
           double z = 0, double w = 1, Vector color = Vector(255, 255, 255)) : Point(x, y, z, w) { v_color = color; }

    //с opt пока вопрос
    Vertex(Options opt) : Point(opt) {}

    Vertex(Vertex &&point) noexcept : Point(point) { v_color = point.v_color; }


    Vertex& operator=
    (const Vertex& other)noexcept
    {
        Point::operator =(other);
        this->v_color = other.v_color;

        return *this;
    }

    Vertex& operator=
    (const Point& other)noexcept
    {
        Point::operator =(other);

        return *this;
    }


    //как нибудь позже надо будет вернуться сюда
    /*Vertex& operator=
    (Vertex&& other)noexcept;

    bool isEqual(const Vertex &B)noexcept;

    bool operator==
    (const Vertex& other)noexcept;

    bool operator!=
    (const Vertex& other)noexcept;

    Vertex & operator+
    (Vertex &other);

    Vertex & operator+=
    (Vertex &other);

    Vertex & operator-
    (Vertex &other);

    Vertex & operator-=
    (Vertex &other);*/



    void set_p_color(const Vector &color);
    Vector get_p_color();

private:
    Vector v_color;
};

#endif // VERTEX_H
