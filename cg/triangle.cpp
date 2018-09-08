#include "Triangle.h"
#include <iostream>

Triangle::Triangle(Object* ob, Indexes &v, Indexes &vt,
                   /*Indexes &vn,*/ int s, int a, QColor c)
{
    this->object = ob;
    this->indexes_vert = v;
    this->indexes_text = vt;
    //this->indexes_norm = vn;
    this->state = s;
    this->attr = a;
    this->color = c;
}

void Triangle::copy(const Triangle& triangle) noexcept
{
    this->object = triangle.object;
    this->indexes_vert = triangle.indexes_vert;
    this->indexes_text = triangle.indexes_text;
    //this->indexes_norm = triangle.indexes_norm;
    this->state = triangle.state;
    this->attr = triangle.attr;
    this->color = triangle.color;
}

void Triangle::destroy() noexcept
{
    object = nullptr;
}

Triangle::Triangle(const Triangle &triangle)
{
    copy(triangle);
}

Triangle::~Triangle()
{
    destroy();
}

Triangle& Triangle::operator=(const Triangle& other) noexcept
{
    destroy();
    copy(other);
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other)noexcept
{
    destroy();
    copy(other);
    other.destroy();
    return *this;
}

// 581 Получить вектор нормали
Vector Triangle::getNormal(std::list<Point> vertix)
const noexcept
{
    // Векторы плоскости, которые векторно умножатся
    // и дадут вектор нормали.
    Vector u, v, n;

    // 3 точки полигона, задающие плоскости
    Point p0, p1, p2;

    // индекс и счетчик количества найденных точек
    int i = 0, kol = 0;

    // https://metanit.com/cpp/tutorial/7.3.php
     for (auto  it = vertix.begin();
          it != vertix.end(); ++it)
     {
         if (i == indexes_vert[0])
         {
             p0 = *it;
             kol++;
         }

         if (i == indexes_vert[1])
         {
             p1 = *it;
             kol++;
         }

         if (i == indexes_vert[2])
         {
             p2 = *it;
             kol++;
         }

         if (kol == 3)
            it = vertix.end();
         i++;
     }

    // Обход вершин осуществляется по часовой стрелке,
    // так что u=pO->p1, v=p0->p2, n=u*v

    u = Vector(p0, p1);
    v = Vector(p0, p2);
    n = Vector::vectorMultiplication(u, v);

    return n;
}
// нормаль для исходного полигона
Vector Triangle::normalOrigin() const noexcept
{
    return getNormal(object->vertex_local);
}

// нормаль для измененного полигона(после преобразо
// ваний из одних координат в другие)
Vector Triangle::normalTrans() const noexcept
{
    return getNormal(object->vertex_trans);
}

/*
// Сравнение полигонов
bool Triangle::isEqual(
    const Triangle &O) noexcept
{
    bool boolObject = this->object == O.object;
    bool boolIndexes = true;
    for (int i = 0; i < 3; i++)
    {
        if (this->indexes[i] == O.indexes[i])
        {
            boolIndexes = false;
            break;
        }
    }

    bool boolInfo = (
                (this->state == O.state)
                &&
                (this->attr == O.attr)
                &&
                (this->color == O.color)
                );

    return (boolObject && boolIndexes && boolInfo);

}

bool Triangle::operator==(const Triangle& other)noexcept
{
    return isEqual(other);
}

bool Triangle::operator!=(const Triangle& other)noexcept
{
    return !isEqual(other);
}
*/
