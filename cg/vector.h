#ifndef VECTOR_H
#define VECTOR_H

class Point;

#include "point.h"
#include <cmath>

#define EPS 1e-6

class Vector
{
private:

public:
    double x, y, z;

    /*Конструкторы */
    Vector()
    {
        x = 0; y = 0; z = 0;
    }

    Vector(Point p1, Point p2);

    Vector(double x1, double y1, double z1,
        double x2, double y2, double z2);
    Vector(double x, double y, double z);

    //Конструкторы копирования
    Vector(Vector &&vector);

    Vector(const Vector &vector);

    Vector& operator=(const Vector& other) noexcept;

    Vector& operator=(Vector&& other)noexcept;

    // Сравнение
    static bool areEqual(const Vector &A, const Vector &B)noexcept;

    bool operator==(const Vector &B)noexcept;

    bool operator!=(const Vector &B)noexcept;

    // Умножения

    static Vector vectorMultiplication(const Vector &vector1,
        const Vector &vector2) noexcept;

    static double scalarMultiplication(const Vector &vector1,
        const Vector &vector2) noexcept;

    Vector operator*(const Vector &v1) noexcept;

    void normalize();

    Point asPoint();
};

#endif // VECTOR_H
