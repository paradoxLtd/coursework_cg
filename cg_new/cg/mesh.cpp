#include "mesh.h"

Mesh::Mesh(std::string fileName)
{
    IndexedModel model = new OBJModel(fileName).ToIndexedModel();

    for(int i = 0; i < model.GetPositions().size(); i++)
    {
        m_vertices.push_back(new Vertex(
                    model.GetPositions().get(i),
                    model.GetTexCoords().get(i),
                    model.GetNormals().get(i)));
    }

    m_indices = model.GetIndices();
}

void Mesh::Draw(RenderContext context, Matrix4f viewProjection, Matrix4f transform, Bitmap texture)
{
    Matrix4f mvp = viewProjection.Mul(transform);
    for(int i = 0; i < m_indices.size(); i += 3)
    {
        context.DrawTriangle(
                m_vertices[m_indices[i]].Transform(mvp, transform),
                m_vertices[m_indices[i + 1]].Transform(mvp, transform),
                m_vertices[m_indices[i + 2]].Transform(mvp, transform), texture);
    }
}
