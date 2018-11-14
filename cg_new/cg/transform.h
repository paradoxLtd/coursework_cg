#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector4f.h"
#include "quaternion.h"
#include "matrix4f.h"

class Transform
{
public:
    Transform();
    Transform(Vector4f &pos);
    Transform(Vector4f &pos, Quaternion &rot, Vector4f &scale);
    Transform SetPos(Vector4f &pos);
    Transform Rotate(Quaternion &rotation);
    Transform LookAt(Vector4f &point, Vector4f &up);
    Quaternion GetLookAtRotation(Vector4f &point, Vector4f &up);
    Matrix4f GetTransform();
    Vector4f GetTransformedPos();
    Quaternion GetTransformedRot();
    Vector4f GetPos();
    Quaternion GetRot();
    Vector4f GetScale();

private:
    Vector4f m_pos;
    Quaternion m_rot;
    Vector4f m_scale;

};

#endif // TRANSFORM_H
