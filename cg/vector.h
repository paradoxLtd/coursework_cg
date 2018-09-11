#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Point;

#include "Point.h"

#define EPS 1e-6

// Прошло проверки, не изменялось, 10.09.18
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

    Vector(Vector v1, Vector v2);

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

    Point asPoint();

    friend std::ostream& operator<<(std::ostream& os,
                                    const Vector& p);

    void normalize();

    static void debug();
};

#endif // VECTOR_H
