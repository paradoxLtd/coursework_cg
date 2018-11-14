#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

#include "vector4f.h"
#include "matrix4f.h"

class Vertex
{
public:


    Vector4f GetPosition() { return m_pos; }
    Vector4f GetTexCoords() { return m_texCoords; }
    Vector4f GetNormal() { return m_normal; }

    Vertex(Vector4f pos, Vector4f texCoords, Vector4f normal);

    Vertex(const Vertex &other);

    Vertex(Vertex &&other);

    Vertex operator=
    (const Vertex& other);

    Vertex operator=
    (Vertex&& other);

    Vertex Transform(Matrix4f transform, Matrix4f normalTransform);

    Vertex PerspectiveDivide();

    float TriangleAreaTimesTwo(Vertex b, Vertex c);

    Vertex Lerp(Vertex other, float lerpAmt);

    bool IsInsideViewFrustum();

    float Get(int index);

    float GetX() { return m_pos.GetX(); }
    float GetY() { return m_pos.GetY(); }

private:
    Vector4f m_pos;
    Vector4f m_texCoords;
    Vector4f m_normal;

};


#endif // VERTEX_H
