#include "Vector.h"

Vector::Vector(Point p1, Point p2)
{
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
    this->z = p2.z - p1.z;
}

// векторное произведение
Vector::Vector(Vector v1, Vector v2)
{
    *this = Vector::vectorMultiplication(v1, v2);
}

Vector::Vector(double x1, double y1, double z1,
    double x2, double y2, double z2)
{
    this->x = x2 - x1;
    this->y = y2 - y1;
    this->z = z2 - z1;
}

Vector::Vector(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// конструктор копирования
Vector::Vector(const Vector &vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}


Vector::Vector(Vector &&vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

Vector& Vector::operator=(const Vector& vector) noexcept
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
    return *this;
}

Vector& Vector::operator=(Vector&& vector)noexcept
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
    return *this;
}

// https://ru.onlinemschool.com/math/library/vector/multiply1/
// i (aybz - azby) - j (axbz - azbx) + k (axby - aybx)
Vector Vector::vectorMultiplication(const Vector &v1,
    const Vector &v2) noexcept
{
    double x = v1.y * v2.z - v1.z * v2.y;
    double y = - (v1.x * v2.z - v1.z * v2.x);
    double z = v1.x * v2.y - v1.y * v2.x;

    Vector a(x, y, z);
    return a;
}

Vector Vector::operator*(const Vector &v1) noexcept
{
    return vectorMultiplication(*this, v1);
}

double Vector::scalarMultiplication(const Vector &vec1, const Vector &vec2) noexcept
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

/*
// Обновление позиции с помощью матрицы
void Cut::update(const t_matrix &matrix)
{
    begin->update(matrix);
    end->update(matrix);
}

void Cut::debug(
    const char* text, int number) noexcept
{
    //debug(text, number);
    begin->debug("Cut Point ", 1);
    end->debug("Cut Point ", 2);
}
*/

bool Vector::areEqual(const Vector &A,
    const Vector &B) noexcept
{
    return ((A.x == B.x) && (A.y == B.y) && (A.z == B.z));
}

bool Vector::operator==(const Vector& other)noexcept
{
    return areEqual(*this, other);
}

bool Vector::operator!=(const Vector& other)noexcept
{
    return !areEqual(*this, other);
}

Point Vector::asPoint()
{
    return Point(x, y, z, 1);
}

void Vector::normalize()
{
    double denom = sqrt(x * x + y * y + z * z);
    std::cout << "denom = " << denom;
    if (fabs(denom) > EPS) {
        this->x /= denom;
        this->y /= denom;
        this->z /= denom;
    }
}

std::ostream& operator<<(std::ostream& os,
                                const Vector& p)
{
    os << "\n Vector: x: " << p.x << ", y: " << p.y <<
                 ", z: " << p.z;
   return os;
}
