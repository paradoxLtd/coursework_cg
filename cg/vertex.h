#ifndef VERTEX_H
#define VERTEX_H

#include "point.h"

class Vertex
{
public:
    Vertex(Point m_pos, Point m_texCoords){
        this->m_pos = m_pos;
        this->m_texCoords = m_texCoords;
    }
    float GetX() { return m_pos.x; }
    float GetY() { return m_pos.y; }
    float GetZ() { return m_pos.z; }

    Vertex(const Vertex &point) {
        this->m_pos = point.m_pos;
        this->m_texCoords = point.m_texCoords;
    }


    //с opt пока вопрос

    Vertex(Vertex &&point) noexcept {
        this->m_pos = point.m_pos;
        this->m_texCoords = point.m_texCoords;
    }


    Vertex& operator=
    (const Vertex& other)noexcept
    {
        this->m_pos = other.m_pos;
        this->m_texCoords = other.m_texCoords;

        return *this;
    }
    /*
    Vertex& operator=
    (const Point& other)noexcept
    {
        Point::operator =(other);

        return *this;
    }*/


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
    Point GetTexCoords();
    Point GetPosition() { return m_pos; }
    Point get_pos(){ return m_pos; }

private:
    Point m_pos;
    Vector v_color; // не используется при текстурах
    Point m_texCoords;
};

#endif // VERTEX_H
