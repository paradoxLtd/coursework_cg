#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>

#define EPSILON  1e3;

class Quaternion
{
public:
    Quaternion() = default;
    Quaternion(double x, double y, double z, double w);
    Quaternion(Vector4f &axis, double angle);

    Quaternion(Matrix4f &rot);

    double Length();
    Quaternion Normalized();
    Quaternion Conjugate();
    Quaternion Mul(double r);
    Quaternion Mul(Quaternion &r);
    Quaternion Mul(Vector4f &r);
    Quaternion Sub(Quaternion &r);
    Quaternion Add(Quaternion &r);

    Matrix4f toRotationMatrix();
    double dot(Quaternion &r);
    Quaternion NLerp(Quaternion &dest, double lerpFactor, bool shortest);
    Quaternion SLerp(Quaternion &dest, double lerpFactor, bool shortest);

    Vector4f getForward();
    Vector4f getBack();
    Vector4f getUp();
    Vector4f getDown();
    Vector4f getRight();
    Vector4f getLeft();
    double getX();
    double getY();
    double getZ();
    double getW();

    bool equals(Quaternion &r);

private:
    double m_x, m_y, m_z, m_w;
};

#endif // QUATERNION_H
