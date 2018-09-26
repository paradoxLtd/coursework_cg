#include "Vector.h"

void Vector::init(double x,
                  double y,
                  double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    name = "Vector";
}

// P1 - точка начало вектора, P2 - точка конца
Vector::Vector(Point p1, Point p2)
{
    init(p2.x - p1.x,
         p2.y - p1.y,
         p2.z - p1.z);
}

// Разность координат *2 - *1, *(x,y,z)
Vector::Vector
    (double x1, double y1, double z1,
     double x2, double y2, double z2)
{
    init(x2 - x1,
         y2 - y1,
         z2 - z1);
}

// векторное произведение векторов v1 и v2
Vector::Vector(Vector v1, Vector v2)
{
    init();
    *this = Vector::vectorMultiplication(
                v1, v2);
}

// классическая инициализация
Vector::Vector(double x, double y, double z)
{
    init(x, y, z);
}

// конструктор копирования
Vector::Vector(const Vector &vector)
{
     init(vector.x,
          vector.y,
          vector.z);
}

// конструктор перемещения
Vector::Vector(Vector &&vector)
{
    init(vector.x,
         vector.y,
         vector.z);
}

// переопределение оператора = для копирования
Vector& Vector::operator=
    (const Vector& vector) noexcept
{
    init(vector.x,
         vector.y,
         vector.z);
    return *this;
}

// переопределение оператора = для перемещения
Vector& Vector::operator=
(Vector&& vector)noexcept
{
    init(vector.x,
         vector.y,
         vector.z);
    return *this;
}

// https://ru.onlinemschool.com/math/library/vector/multiply1/
// i (aybz - azby) - j (axbz - azbx) + k (axby - aybx)
Vector Vector::vectorMultiplication
    (const Vector &v1,
     const Vector &v2) noexcept
{
    double x = v1.y * v2.z - v1.z * v2.y;
    double y = - (v1.x * v2.z - v1.z * v2.x);
    double z = v1.x * v2.y - v1.y * v2.x;

    Vector a(x, y, z);
    return a;
}

Vector Vector::operator*
    (const Vector &v1) noexcept
{
    return vectorMultiplication(*this, v1);
}

double Vector::scalarMultiplication
    (const Vector &vec1,
     const Vector &vec2) noexcept
{
    return vec1.x * vec2.x +
           vec1.y * vec2.y +
           vec1.z * vec2.z;
}

// Сравнение векторов
bool Vector::areEqual(const Vector &A,
    const Vector &B) noexcept
{
    return (
                (fabs(A.x - B.x) > 0)
                &&
                (fabs(A.y - B.y) > 0)
                &&
                (fabs(A.z - B.z) > 0)
           );
}

// Переопределение оператора ==
bool Vector::operator==
    (const Vector& other) noexcept
{
    return areEqual(*this, other);
}

// Переопределение оператора !=
bool Vector::operator!=
    (const Vector& other) noexcept
{
    return !areEqual(*this, other);
}

Vector &Vector::operator+=
    (Vector &other) noexcept
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

Vector &Vector::operator+
    (Vector &other) noexcept
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

// Преобразование к типу Point
Point Vector::asPoint()
{
    return Point(x, y, z, 1);
}

// Нормализация вектора
void Vector::normalize()
{
    double denom = sqrt(x * x +
                        y * y +
                        z * z);
    if (fabs(denom) > EPS)
    {
        this->x /= denom;
        this->y /= denom;
        this->z /= denom;
    }
}

// Переопределение ввывода
std::ostream& operator<<
    (std::ostream& os, const Vector& p)
{
    os << "\n" << p.name <<
          "(x: " << p.x <<
          ", y: " << p.y <<
          ", z: " << p.z <<
          ")";
   return os;
}
