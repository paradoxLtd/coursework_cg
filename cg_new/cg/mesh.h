#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>

#include "vertex.h"
#include "matrix4f.h"
#include "rendercontext.h"
#include "indexedmodel.h"
#include "objmodel.h"
#include "texture.h"

class Mesh
{
public:
    Mesh(std::string fileName);
    void Draw(RenderContext context, Matrix4f viewProjection,
              Matrix4f transform, Texture texture);
private:
    std::vector<Vertex>  m_vertices;
    std::vector<int> m_indices;
};

#endif // MESH_H
