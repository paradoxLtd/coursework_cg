#include "vertex.h"

void Vertex::set_p_color(const Vector &color)
{
    this->v_color = color;
}

Vector Vertex::get_p_color()
{
    return this->v_color;
}

Point Vertex::GetTexCoords()
{
    return this->m_texCoords;
}
