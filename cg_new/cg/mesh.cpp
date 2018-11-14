#include "mesh.h"

Mesh::Mesh(std::string fileName)
{
    IndexedModel model = OBJModel(fileName).ToIndexedModel();

    for(int i = 0; i < model.GetPositions().size(); i++)
    {
        m_vertices.push_back(Vertex(
                    model.GetPositions()[i],
                    model.GetTexCoords()[i],
                    model.GetNormals()[i]));
    }

    m_indices = model.GetIndices();
}

void Mesh::Draw(RenderContext context, Matrix4f viewProjection, Matrix4f transform, Texture texture)
{

    Matrix4f mvp = viewProjection.Mul(transform);



    for(int i = 0; i < m_indices.size(); i += 3)
    {

        //qDebug() << "--------------------x:";
        /*
        qDebug() << m_vertices[m_indices[i]].GetX() << " y:"
                 << m_vertices[m_indices[i]].GetY() << " z:" <<
                    m_vertices[m_indices[i]].GetZ();
        qDebug() << "i + 1" << m_vertices[m_indices[i + 1]].GetX() << " y:"
                 << m_vertices[m_indices[i + 1]].GetY() << " z:" <<
                    m_vertices[m_indices[i + 1]].GetZ();
                    */

        qDebug() << "index:" << m_indices[i];
        qDebug() << "!!!!!!!!!!!!!!!!!!!!x:";
        qDebug() << m_vertices[m_indices[i]].Transform(mvp, transform).GetX() << " y:"
                 << m_vertices[m_indices[i]].Transform(mvp, transform).GetY() << " z:" <<
                    m_vertices[m_indices[i]].Transform(mvp, transform).GetZ();

        context.DrawTriangle(
                m_vertices[m_indices[i]].Transform(mvp, transform),
                m_vertices[m_indices[i + 1]].Transform(mvp, transform),
                m_vertices[m_indices[i + 2]].Transform(mvp, transform), texture);

        //qDebug() << "after";
        //qDebug() << m_vertices[m_indices[i]].Transform(mvp, transform).GetX() << " " << m_vertices[m_indices[i]].Transform(mvp, transform).GetY();
    }
}
