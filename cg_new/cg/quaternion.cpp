#include "quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    this->m_w = w;
}

Quaternion::Quaternion(Vector4f axis, float angle)
{
    float sinHalfAngle =  sinf(angle / 2);
    float cosHalfAngle = cosf(angle / 2);

    this->m_x = axis.GetX() * sinHalfAngle;
    this->m_y = axis.GetY() * sinHalfAngle;
    this->m_z = axis.GetZ() * sinHalfAngle;
    this->m_w = cosHalfAngle;
}

Quaternion::Quaternion(Matrix4f rot)
{
    float trace = rot.Get(0, 0) + rot.Get(1, 1) + rot.Get(2, 2);

    if(trace > 0)
    {
        float s = 0.5f / sqrtf(trace+ 1.0f);
        m_w = 0.25f / s;
        m_x = (rot.Get(1, 2) - rot.Get(2, 1)) * s;
        m_y = (rot.Get(2, 0) - rot.Get(0, 2)) * s;
        m_z = (rot.Get(0, 1) - rot.Get(1, 0)) * s;
    }
    else
    {
        if(rot.Get(0, 0) > rot.Get(1, 1) &&
                rot.Get(0, 0) > rot.Get(2, 2))
        {
            float s = 2.0f * static_cast<float>(
                        sqrtf(1.0f + rot.Get(0, 0) -
                             rot.Get(1, 1) - rot.Get(2, 2)));
            m_w = (rot.Get(1, 2) - rot.Get(2, 1)) / s;
            m_x = 0.25f * s;
            m_y = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
            m_z = (rot.Get(2, 0) + rot.Get(0, 2)) / s;
        }
        else if(rot.Get(1, 1) > rot.Get(2, 2))
        {
            float s = 2.0f * sqrtf(1.0f + rot.Get(1, 1) - rot.Get(0, 0) - rot.Get(2, 2));
            m_w = (rot.Get(2, 0) - rot.Get(0, 2)) / s;
            m_x = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
            m_y = 0.25f * s;
            m_z = (rot.Get(2, 1) + rot.Get(1, 2)) / s;
        }
        else
        {
            float s = 2.0f * sqrtf(1.0f + rot.Get(2, 2) -
                                   rot.Get(0, 0) - rot.Get(1, 1));
            m_w = (rot.Get(0, 1) - rot.Get(1, 0) ) / s;
            m_x = (rot.Get(2, 0) + rot.Get(0, 2) ) / s;
            m_y = (rot.Get(1, 2) + rot.Get(2, 1) ) / s;
            m_z = 0.25f * s;
        }
    }

    float length = sqrtf(m_x * m_x + m_y * m_y +
                         m_z * m_z + m_w * m_w);
    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;
}

float Quaternion::Length()
{
    return sqrtf(m_x * m_x + m_y * m_y +
                m_z * m_z + m_w * m_w);
}

Quaternion Quaternion::Normalized()
{
    float length = Length();

    return Quaternion(m_x / length, m_y / length,
                      m_z / length, m_w / length);
}

Quaternion Quaternion::Conjugate()
{
    return Quaternion(-m_x, -m_y, -m_z, m_w);
}

Quaternion Quaternion::Mul(float r)
{
    return  Quaternion(m_x * r, m_y * r, m_z * r, m_w * r);
}

Quaternion Quaternion::Mul(Quaternion r)
{
    float w_ = m_w * r.GetW() - m_x * r.GetX() -
            m_y * r.GetY() - m_z * r.GetZ();
    float x_ = m_x * r.GetW() + m_w * r.GetX() +
            m_y * r.GetZ() - m_z * r.GetY();
    float y_ = m_y * r.GetW() + m_w * r.GetY() +
            m_z * r.GetX() - m_x * r.GetZ();
    float z_ = m_z * r.GetW() + m_w * r.GetZ() +
            m_x * r.GetY() - m_y * r.GetX();

    return Quaternion(x_, y_, z_, w_);
}

Quaternion Quaternion::Mul(Vector4f r)
{
    float w_ = -m_x * r.GetX() - m_y * r.GetY() - m_z * r.GetZ();
    float x_ =  m_w * r.GetX() + m_y * r.GetZ() - m_z * r.GetY();
    float y_ =  m_w * r.GetY() + m_z * r.GetX() - m_x * r.GetZ();
    float z_ =  m_w * r.GetZ() + m_x * r.GetY() - m_y * r.GetX();

    return Quaternion(x_, y_, z_, w_);
}

Quaternion Quaternion::Sub(Quaternion r)
{
    return Quaternion(m_x - r.GetX(), m_y - r.GetY(),
                      m_z - r.GetZ(), m_w - r.GetW());
}

Quaternion Quaternion::Add(Quaternion r)
{
    return Quaternion(m_x + r.GetX(), m_y + r.GetY(),
                      m_z + r.GetZ(), m_w + r.GetW());
}

Matrix4f Quaternion::toRotationMatrix()
{
    Vector4f forward =  Vector4f(2.0f * (m_x * m_z - m_w * m_y), 2.0f * (m_y * m_z + m_w * m_x),
                                 1.0f - 2.0f * (m_x * m_x + m_y * m_y));
    Vector4f up = Vector4f(2.0f * (m_x * m_y + m_w * m_z), 1.0f - 2.0f * (m_x * m_x + m_z * m_z),
                           2.0f * (m_y * m_z - m_w * m_x));
    Vector4f right = Vector4f(1.0f - 2.0f * (m_y * m_y + m_z * m_z), 2.0f * (m_x * m_y - m_w * m_z),
                              2.0f * (m_x * m_z + m_w * m_y));

    return Matrix4f().InitRotation(forward, up, right);
}

float Quaternion::dot(Quaternion r)
{
    return m_x * r.GetX() + m_y * r.GetY() +
            m_z * r.GetZ() + m_w * r.GetW();
}

Quaternion Quaternion::NLerp(Quaternion dest,
                             float lerpFactor, bool shortest)
{
    Quaternion correctedDest = dest;

    if(shortest && this->dot(dest) < 0)
        correctedDest = Quaternion(-dest.GetX(),
                                   -dest.GetY(), -dest.GetZ(),
                                   -dest.GetW());

    return correctedDest.Sub(*this).Mul(lerpFactor).
            Add(*this).Normalized();
}

Quaternion Quaternion::SLerp(Quaternion dest, float lerpFactor,
                             bool shortest)
{
    float cos = this->dot(dest);
    Quaternion correctedDest = dest;

    if(shortest && cos < 0)
    {
        cos = -cos;
        correctedDest = Quaternion(-dest.GetX(), -dest.GetY(),
                                   -dest.GetZ(), -dest.GetW());
    }

    if(fabsf(cos - 1) > EPSILON)
        return NLerp(correctedDest, lerpFactor, false);

    float sinus = sqrtf(1.0f - cos * cos);
    float angle = atan2f(sinus, cos); //what is this?)
    float invSin =  1.0f/sinus;

    float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
    float destFactor = sinf((lerpFactor) * angle) * invSin;

    return this->Mul(srcFactor).Add(correctedDest.Mul(destFactor));
}

Vector4f Quaternion::GetForward()
{
    return Vector4f(0,0,1,1).Rotate(this);
}

Vector4f Quaternion::GetBack()
{
    return Vector4f(0,0,-1,1).Rotate(this);
}

Vector4f Quaternion::GetUp()
{
    return Vector4f(0,1,0,1).Rotate(this);
}

Vector4f Quaternion::GetDown()
{
    return Vector4f(0,-1,0,1).Rotate(this);
}

Vector4f Quaternion::GetRight()
{
    return Vector4f(1,0,0,1).Rotate(this);
}

#include <iostream>
Vector4f Quaternion::GetLeft()
{
    return Vector4f(-1,0,0,1).Rotate(this);
}

float Quaternion::GetX()
{
    return this->m_x;
}

float Quaternion::GetY()
{
    return this->m_y;
}

float Quaternion::GetZ()
{
    return this->m_z;
}

float Quaternion::GetW()
{
    return this->m_w;
}

bool Quaternion::equals(Quaternion &r)
{
    return (fabsf(m_x - r.GetX()) < EPSILON &&
            fabsf(m_y - r.GetY()) < EPSILON &&
            fabsf(m_z - r.GetZ()) < EPSILON &&
            fabsf(m_w - r.GetW()) < EPSILON);
}
