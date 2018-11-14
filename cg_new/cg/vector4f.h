#ifndef VECTOR4F_H
#define VECTOR4F_H
#include <string>

class Quaternion;
//#include "quaternion.h"

class Vector4f
{
public:
    //Vector4f(float x, float y, float z);
    Vector4f(float x, float y, float z, float w);

    Vector4f(float x = 0, float y = 0, float z = 0);

    float Length();

    float Max();

    float Dot(Vector4f r);

    Vector4f Cross(Vector4f r);

    Vector4f Normalized();

    Vector4f Rotate(Vector4f axis, float angle);

    Vector4f Rotate(Quaternion *rotation);

    Vector4f Lerp(Vector4f dest, float lerpFactor);

    Vector4f Add(Vector4f r);

    Vector4f Add(float r);

    Vector4f Sub(Vector4f r);

    Vector4f Sub(float r);

    Vector4f Mul(Vector4f r);

    Vector4f Mul(float r);

    Vector4f Div(Vector4f r);

    Vector4f Div(float r);

    Vector4f Abs();

    std::string toString();

    float GetX();

    float GetY();

    float GetZ();

    float GetW();

    bool equals(Vector4f r);

    // Добавлены конструкторы копировния для корректной работы
    // objmodel
    Vector4f(const Vector4f &other);

    Vector4f(Vector4f &&other);

    Vector4f operator=
    (const Vector4f& other);

    Vector4f operator=
    (Vector4f&& other);
    //


private:
    /* Убраны модификаторы const, чтобы можно было изменить
     * значения в конструкторах копирования
    */
    float x;
    float y;
    float z;
    float w;
};


#endif // VECTOR4F_H
