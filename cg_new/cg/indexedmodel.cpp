#include "indexedmodel.h"

void IndexedModel::calcNormals()
{
    int i0, i1, i2;

    for(int i = 0; i < m_indices.size(); i += 3)
    {
        i0 = m_indices[i];
        i1 = m_indices[i + 1];
        i2 = m_indices[i + 2];

        Vector4f v1 = m_positions[i1].Sub(m_positions[i0]);
        Vector4f v2 = m_positions[i2].Sub(m_positions[i0]);

        Vector4f normal = v1.Cross(v2).Normalized();

        m_normals.set(i0, m_normals[i0].Add(normal));
        m_normals.set(i1, m_normals[i1].Add(normal));
        m_normals.set(i2, m_normals[i2].Add(normal));
    }

    for(int i = 0; i < m_normals.size(); i++)
        m_normals.set(i, m_normals[i].Normalized());
}

void IndexedModel::calcTangents()
{
    int i0, i1, i2;

    for(int i = 0; i < m_indices.size(); i += 3)
    {
        i0 = m_indices[i];
        i1 = m_indices[i + 1];
        i2 = m_indices[i + 2];

        Vector4f edge1 = m_positions[i1].Sub(m_positions[i0]);
        Vector4f edge2 = m_positions[i2].Sub(m_positions[i0]);

        float deltaU1 = m_texCoords[i1].GetX() - m_texCoords[i0].GetX();
        float deltaV1 = m_texCoords[i1].GetY() - m_texCoords[i0].GetY();
        float deltaU2 = m_texCoords[i2].GetX() - m_texCoords[i0].GetX();
        float deltaV2 = m_texCoords[i2].GetY() - m_texCoords[i0].GetY();

        float dividend = (deltaU1*deltaV2 - deltaU2*deltaV1);
        float f = dividend == 0 ? 0.0f : 1.0f/dividend;

        Vector4f tangent = new Vector4f(
                f * (deltaV2 * edge1.GetX() - deltaV1 * edge2.GetX()),
                f * (deltaV2 * edge1.GetY() - deltaV1 * edge2.GetY()),
                f * (deltaV2 * edge1.GetZ() - deltaV1 * edge2.GetZ()),
                0);

        m_tangents.set(i0, m_tangents[i0].Add(tangent));
        m_tangents.set(i1, m_tangents[i1].Add(tangent));
        m_tangents.set(i2, m_tangents[i2].Add(tangent));
    }

    for(int i = 0; i < m_tangents.size(); i++)
        m_tangents.set(i, m_tangents[i].Normalized());
}

std::vector<Vector4f> IndexedModel::getPositions()
{
    return this->m_positions;
}

std::vector<Vector4f> IndexedModel::getTexCoords()
{
    return this->m_texCoords;
}

std::vector<Vector4f> IndexedModel::getNormals()
{
    return this->m_normals;
}

std::vector<Vector4f> IndexedModel::getTangents()
{
    return this->m_tangents;
}

std::vector<int> IndexedModel::getIndices()
{
    return this->m_indices;
}
