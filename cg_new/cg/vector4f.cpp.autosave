#include "vector4f.h"
#include <cmath>
#include <algorithm>

Vector4f::Vector4f(float x, float y, float z,
                   float w = 1) : x(x), y(y), z(z), w(w) {}

float Vector4f::Length()
{
    return static_cast<float>(sqrt(x * x + y * y + z * z + w * w));
}

float Vector4f::Max()
{
    return std::max(std::max(x, y), std::max(z, w));
}

float Vector4f::Dot(Vector4f r)
{
    return x * r.GetX() + y * r.GetY() + z * r.GetZ() + w * r.GetW();
}

Vector4f Vector4f::Cross(Vector4f r)
{
    float x_ = y * r.GetZ() - z * r.GetY();
    float y_ = z * r.GetX() - x * r.GetZ();
    float z_ = x * r.GetY() - y * r.GetX();
    Vector4f v(x_, y_, z_, 0);

    return v;
}

Vector4f Vector4f::Normalized()
{
    float length = Length();

    Vector4f v(x / length, y / length, z / length, w / length);
    return v;
}

Vector4f Vector4f::Rotate(Vector4f axis, float angle)
{
    float sinAngle = (float)sin(-angle);
    float cosAngle = (float)cos(-angle);

    this->Cross(axis.Mul(sinAngle)).Add(           //Rotation on local X
            (this->Mul(cosAngle)).Add(                     //Rotation on local Z
                    axis.Mul(this->Dot(axis.Mul(1 - cosAngle))))); //Rotation on local Y
}
#include "quaternion.h"
Vector4f Vector4f::Rotate(Quaternion *rotation)
{
    Quaternion conjugate = rotation->Conjugate();

    Quaternion w = rotation->Mul(*this).Mul(conjugate);

    return Vector4f(w.GetX(), w.GetY(), w.GetZ(), 1.0f);
}

Vector4f Vector4f::Lerp(Vector4f dest, float lerpFactor)
{
    return dest.Sub(*this).Mul(lerpFactor).Add(*this);
}

Vector4f Vector4f::Add(Vector4f r)
{
    return Vector4f(x + r.GetX(), y + r.GetY(), z + r.GetZ(), w + r.GetW());
}

Vector4f Vector4f::Add(float r)
{
    return Vector4f(x + r, y + r, z + r, w + r);
}

Vector4f Vector4f::Sub(Vector4f r)
{
    return Vector4f(x - r.GetX(), y - r.GetY(), z - r.GetZ(), w - r.GetW());
}

Vector4f Vector4f::Sub(float r)
{
    return Vector4f(x - r, y - r, z - r, w - r);
}

Vector4f Vector4f::Mul(Vector4f r)
{
    return Vector4f(x * r.GetX(), y * r.GetY(), z * r.GetZ(), w * r.GetW());
}

Vector4f Vector4f::Mul(float r)
{
    return Vector4f(x * r, y * r, z * r, w * r);
}

Vector4f Vector4f::Div(Vector4f r)
{
    return Vector4f(x / r.GetX(), y / r.GetY(), z / r.GetZ(), w / r.GetW());
}

Vector4f Vector4f::Div(float r)
{
    return Vector4f(x / r, y / r, z / r, w / r);
}

Vector4f Vector4f::Abs()
{
    return Vector4f(fabs(x), fabs(y), fabs(z), fabs(w));
}

std::string Vector4f::toString()
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) +
            ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}

float Vector4f::GetX()
{
    return x;
}

float Vector4f::GetY()
{
    return y;
}

float Vector4f::GetZ()
{
    return z;
}

float Vector4f::GetW()
{
    return w;
}

bool Vector4f::equals(Vector4f r)
{
    return x == r.GetX() && y == r.GetY() && z == r.GetZ() && w == r.GetW();
}

Vector4f::Vector4f(const Vector4f &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}

Vector4f::Vector4f(Vector4f &&other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}

Vector4f& Vector4f::operator=
(const Vector4f& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}

Vector4f& Vector4f::operator=
(Vector4f&& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}
