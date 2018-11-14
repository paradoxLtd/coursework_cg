#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "vector4f.h"
#include "matrix4f.h"

#define EPSILON  1e-3f

class Quaternion
{
public:
    Quaternion() = default;
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector4f axis, float angle);

    Quaternion(Matrix4f rot);

    float Length();
    Quaternion Normalized();
    Quaternion Conjugate();
    Quaternion Mul(float r);
    Quaternion Mul(Quaternion r);
    Quaternion Mul(Vector4f r);
    Quaternion Sub(Quaternion r);
    Quaternion Add(Quaternion r);

    Matrix4f toRotationMatrix();
    float dot(Quaternion r);
    Quaternion NLerp(Quaternion dest, float lerpFactor,
                     bool shortest);
    Quaternion SLerp(Quaternion dest, float lerpFactor,
                     bool shortest);

    Vector4f GetForward();
    Vector4f GetBack();
    Vector4f GetUp();
    Vector4f GetDown();
    Vector4f GetRight();
    Vector4f GetLeft();
    float GetX();
    float GetY();
    float GetZ();
    float GetW();

    bool equals(Quaternion &r);

private:
    float m_x, m_y, m_z, m_w;
};

#endif // QUATERNION_H
