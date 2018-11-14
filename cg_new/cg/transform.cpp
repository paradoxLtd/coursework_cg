#include "transform.h"

Transform::Transform()
{
    this->m_pos = Vector4f(0, 0, 0, 0);
    this->m_scale = Vector4f(1, 1, 1, 1);
}

Transform::Transform(Vector4f pos)
{
    this->m_pos = pos;
    this->m_scale = Vector4f(1, 1, 1, 1);
    this->m_rot = Quaternion(0, 0, 0, 1);
}

Transform::Transform(Vector4f pos, Quaternion rot,
                     Vector4f scale)
{
    this->m_pos = pos;
    this->m_rot = rot;
    this->m_scale = scale;
}

Transform Transform::SetPos(Vector4f pos)
{
    return Transform(pos, m_rot, m_scale);
}

Transform Transform::Rotate(Quaternion rotation)
{
    return Transform(m_pos, rotation.Mul(m_rot).Normalized(),
                     m_scale);
}

Transform Transform::LookAt(Vector4f point, Vector4f up)
{
    return Rotate(GetLookAtRotation(point, up));
}

Quaternion Transform::GetLookAtRotation(Vector4f point,
                                        Vector4f up)
{
    Matrix4f mtx;

    return Quaternio(mtx.InitRotation(
                          point.Sub(m_pos).Normalized(), up));
}

Matrix4f Transform::GetTransform()
{
    Matrix4f mtx;

    Matrix4f translationMatrix = mtx.InitTranslation(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ());
    Matrix4f rotationMatrix = m_rot.toRotationMatrix();
    Matrix4f scaleMatrix = mtx.InitScale(m_scale.GetX(), m_scale.GetY(), m_scale.GetZ());

    return translationMatrix.Mul(rotationMatrix.Mul(scaleMatrix));
}

Quaternion Transform::GetTransformedRot()
{
    return this->m_pos;
}

Vector4f Transform::GetPos()
{
    return this->m_rot;
}

Quaternion Transform::GetRot()
{
    return this->m_rot;
}

Vector4f Transform::GetScale()
{
    return this->m_scale;
}
