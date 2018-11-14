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

    Quaternion(const Quaternion &other) {
        this->m_x = other.m_x;
        this->m_y = other.m_y;
        this->m_z = other.m_z;
        this->m_w = other.m_w;
    }

    Quaternion(Quaternion &&other ) {
        this->m_x = other.m_x;
        this->m_y = other.m_y;
        this->m_z = other.m_z;
        this->m_w = other.m_w;
    }

    Quaternion operator=
    (const Quaternion& other) {
        this->m_x = other.m_x;
        this->m_y = other.m_y;
        this->m_z = other.m_z;
        this->m_w = other.m_w;
        return *this;
    }

    Quaternion operator=
    (Quaternion&& other) {
        this->m_x = other.m_x;
        this->m_y = other.m_y;
        this->m_z = other.m_z;
        this->m_w = other.m_w;
        return *this;
    }

private:
    float m_x, m_y, m_z, m_w;
};

#endif // QUATERNION_H
