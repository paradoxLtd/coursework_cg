#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include "vertex.h"
#include "matrix4f.h"
#include "rendercontext.h"

class Mesh
{
private:
    std::vector<Vertex>  m_vertices;
    std::vector<int> m_indices;

    Mesh(std::string fileName);
    void Draw(RenderContext context, Matrix4f viewProjection, Matrix4f transform, Bitmap texture);
}

#endif // MESH_H
