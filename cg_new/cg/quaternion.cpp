#include "quaternion.h"

Quaternion::Quaternion(double x, double y, double z, double w)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    this->m_w = w;
}

Quaternion::Quaternion(Vector4f &axis, double angle)
{
    double sinHalfAngle =  sin(angle / 2);
    double cosHalfAngle = cos(angle / 2);

    this->m_x = axis.GetX() * sinHalfAngle;
    this->m_y = axis.GetY() * sinHalfAngle;
    this->m_z = axis.GetZ() * sinHalfAngle;
    this->m_w = cosHalfAngle;
}

Quaternion::Quaternion(Matrix4f &rot)
{
    double trace = rot.Get(0, 0) + rot.Get(1, 1) + rot.Get(2, 2);

    if(trace > 0)
    {
        double s = 0.5f / sqrt(trace+ 1.0f);
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
            double s = 2.0f * (double)sqrt(1.0f + rot.Get(0, 0) - rot.Get(1, 1) - rot.Get(2, 2));
            m_w = (rot.Get(1, 2) - rot.Get(2, 1)) / s;
            m_x = 0.25f * s;
            m_y = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
            m_z = (rot.Get(2, 0) + rot.Get(0, 2)) / s;
        }
        else if(rot.Get(1, 1) > rot.Get(2, 2))
        {
            double s = 2.0f * sqrt(1.0f + rot.Get(1, 1) - rot.Get(0, 0) - rot.Get(2, 2));
            m_w = (rot.Get(2, 0) - rot.Get(0, 2)) / s;
            m_x = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
            m_y = 0.25f * s;
            m_z = (rot.Get(2, 1) + rot.Get(1, 2)) / s;
        }
        else
        {
            double s = 2.0f * sqrt(1.0f + rot.Get(2, 2) -
                                   rot.Get(0, 0) - rot.Get(1, 1));
            m_w = (rot.Get(0, 1) - rot.Get(1, 0) ) / s;
            m_x = (rot.Get(2, 0) + rot.Get(0, 2) ) / s;
            m_y = (rot.Get(1, 2) + rot.Get(2, 1) ) / s;
            m_z = 0.25f * s;
        }
    }

    double length = sqrt(m_x * m_x + m_y * m_y +
                         m_z * m_z + m_w * m_w);
    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;
}

double Quaternion::Length()
{
    return sqrt(m_x * m_x + m_y * m_y +
                m_z * m_z + m_w * m_w);
}

Quaternion Quaternion::Normalized()
{
    double length = Length();

    return Quaternion(m_x / length, m_y / length,
                      m_z / length, m_w / length);
}

Quaternion Quaternion::Conjugate()
{
    return Quaternion(-m_x, -m_y, -m_z, m_w);
}

Quaternion Quaternion::Mul(double r)
{
    return  Quaternion(m_x * r, m_y * r, m_z * r, m_w * r);
}

Quaternion Quaternion::Mul(Quaternion r)
{
    double w_ = m_w * r.GetW() - m_x * r.GetX() -
            m_y * r.GetY() - m_z * r.GetZ();
    double x_ = m_x * r.GetW() + m_w * r.GetX() +
            m_y * r.GetZ() - m_z * r.GetY();
    double y_ = m_y * r.GetW() + m_w * r.GetY() +
            m_z * r.GetX() - m_x * r.GetZ();
    double z_ = m_z * r.GetW() + m_w * r.GetZ() +
            m_x * r.GetY() - m_y * r.GetX();

    return Quaternion(x_, y_, z_, w_);
}

Quaternion Quaternion::Mul(Vector4f r)
{
    double w_ = -m_x * r.GetX() - m_y * r.GetY() - m_z * r.GetZ();
    double x_ =  m_w * r.GetX() + m_y * r.GetZ() - m_z * r.GetY();
    double y_ =  m_w * r.GetY() + m_z * r.GetX() - m_x * r.GetZ();
    double z_ =  m_w * r.GetZ() + m_x * r.GetY() - m_y * r.GetX();

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

double Quaternion::dot(Quaternion r)
{
    return m_x * r.GetX() + m_y * r.GetY() +
            m_z * r.GetZ() + m_w * r.GetW();
}

Quaternion Quaternion::NLerp(Quaternion dest,
                             double lerpFactor, bool shortest)
{
    Quaternion correctedDest = dest;

    if(shortest && this->dot(dest) < 0)
        correctedDest = Quaternion(-dest.GetX(),
                                   -dest.GetY(), -dest.GetZ(),
                                   -dest.GetW());

    return correctedDest.Sub(*this).Mul(lerpFactor).
            Add(*this).Normalized();
}

Quaternion Quaternion::SLerp(Quaternion dest, double lerpFactor,
                             bool shortest)
{
    double cos = this->dot(dest);
    Quaternion correctedDest = dest;

    if(shortest && cos < 0)
    {
        cos = -cos;
        correctedDest = Quaternion(-dest.GetX(), -dest.GetY(),
                                   -dest.GetZ(), -dest.GetW());
    }

    if(fabs(cos) > (1 - EPSILON))
        return NLerp(correctedDest, lerpFactor, false);

    double sinus = sqrt(1.0f - cos * cos);
    double angle = atan2(sinus, cos); //what is this?)
    double invSin =  1.0f/sinus;

    double srcFactor = sin((1.0f - lerpFactor) * angle) * invSin;
    double destFactor = sin((lerpFactor) * angle) * invSin;

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

Vector4f Quaternion::GetLeft()
{
    return Vector4f(-1,0,0,1).Rotate(this);
}

double Quaternion::GetX()
{
    return this->m_x;
}

double Quaternion::GetY()
{
    return this->m_y;
}

double Quaternion::GetZ()
{
    return this->m_z;
}

double Quaternion::GetW()
{
    return this->m_w;
}

bool Quaternion::equals(Quaternion &r)
{
    return m_x == r.GetX() && m_y == r.GetY() && m_z == r.GetZ() && m_w == r.GetW();
}
