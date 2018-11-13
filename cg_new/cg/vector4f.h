#ifndef VECTOR4F_H
#define VECTOR4F_H
#include <string>
class Vector4f
{
    Vector4f(float x, float y, float z, float w);

    Vector4f(float x, float y, float z);

    float Length();

    float Max();

    float Dot(Vector4f r);

    Vector4f Cross(Vector4f r);

    Vector4f Normalized();

    Vector4f Rotate(Vector4f axis, float angle);

    Vector4f Rotate(Quaternion rotation);

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

private:
    const float x;
    const float y;
    const float z;
    const float w;
};


#endif // VECTOR4F_H
