#include "vertex.h"
#include "math.h"

Vertex::Vertex(Vector4f pos, Vector4f texCoords, Vector4f normal)
{
    m_pos = pos;
    m_texCoords = texCoords;
    m_normal = normal;
}

Vertex Vertex::Transform(Matrix4f transform, Matrix4f normalTransform) {
    return Vertex(transform.Transform(m_pos),
                  m_texCoords,
                  normalTransform.Transform(m_normal).Normalized());
}

Vertex Vertex::PerspectiveDivide() {
    return Vertex(Vector4f(m_pos.GetX()/m_pos.GetW(),
                           m_pos.GetY()/m_pos.GetW(),
                           m_pos.GetZ()/m_pos.GetW(),
                           m_pos.GetW()),
                  m_texCoords, m_normal);
}

float Vertex::TriangleAreaTimesTwo(Vertex b, Vertex c) {
    float x1 = b.GetX() - m_pos.GetX();
    float y1 = b.GetY() - m_pos.GetY();

    float x2 = c.GetX() - m_pos.GetX();
    float y2 = c.GetY() - m_pos.GetY();

    return (x1 * y2 - x2 * y1);
}

Vertex Vertex::Lerp(Vertex other, float lerpAmt) {
    return Vertex(m_pos.Lerp(other.GetPosition(), lerpAmt),
                  m_texCoords.Lerp(other.GetTexCoords(), lerpAmt),
                  m_normal.Lerp(other.GetNormal(), lerpAmt));
}

/* Для работы с float используется fabsf
 * https://en.cppreference.com/w/c/numeric/math/fabs
 */
bool Vertex::IsInsideViewFrustum() {
    return
        fabsf(m_pos.GetX()) <= fabsf(m_pos.GetW()) &&
        fabsf(m_pos.GetY()) <= fabsf(m_pos.GetW()) &&
        fabsf(m_pos.GetZ()) <= fabsf(m_pos.GetW());
}

float Vertex::Get(int index)
{
    switch(index)
    {
        case 0:
            return m_pos.GetX();
        case 1:
            return m_pos.GetY();
        case 2:
            return m_pos.GetZ();
        case 3:
            return m_pos.GetW();
        default:
            std::cout << "overflow in Vertex::Get\n";
            return 0;
    }
}
