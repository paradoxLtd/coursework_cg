#include "indexedmodel.h"

void IndexedModel::calcNormals() {
    size_t i0, i1, i2;

    for(size_t i = 0; i < m_indices.size(); i += 3) {
        i0 = m_indices[i];
        i1 = m_indices[i + 1];
        i2 = m_indices[i + 2];

        Vector4f v1 = m_positions[i1].Sub(m_positions[i0]);
        Vector4f v2 = m_positions[i2].Sub(m_positions[i0]);

        Vector4f normal = v1.Cross(v2).Normalized();

        m_normals[i0] = m_normals[i0].Add(normal);
        m_normals[i1] = m_normals[i1].Add(normal);
        m_normals[i2] = m_normals[i2].Add(normal);
    }

    for(size_t i = 0; i < m_normals.size(); i++) {
        m_normals[i] = m_normals[i].Normalized();
    }
}

void IndexedModel::calcTangents() {
    int i0, i1, i2;

    for(int i = 0; i < m_indices.size(); i += 3) {
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
        float f = (fabsf(dividend) < 0.001f) ? 0.0f : 1.0f/dividend;

        Vector4f tangent = Vector4f(
                f * (deltaV2 * edge1.GetX() - deltaV1 * edge2.GetX()),
                f * (deltaV2 * edge1.GetY() - deltaV1 * edge2.GetY()),
                f * (deltaV2 * edge1.GetZ() - deltaV1 * edge2.GetZ()),
                0);

        m_tangents[i0] = m_tangents[i0].Add(tangent);
        m_tangents[i1] = m_tangents[i1].Add(tangent);
        m_tangents[i2] = m_tangents[i2].Add(tangent);
    }

    for(int i = 0; i < m_tangents.size(); i++) {
        m_tangents[i] = m_tangents[i].Normalized();
    }
}

std::vector<Vector4f> IndexedModel::GetPositions() const {
    return this->m_positions;
}

std::vector<Vector4f> IndexedModel::GetTexCoords() const {
    return this->m_texCoords;
}

std::vector<Vector4f> IndexedModel::GetNormals() const {
    return this->m_normals;
}

std::vector<Vector4f> IndexedModel::GetTangents() const {
    return this->m_tangents;
}

std::vector<int> IndexedModel::GetIndices() const {
    return this->m_indices;
}

void IndexedModel::PushPosition(Vector4f vector) {
    m_positions.push_back(vector);
}
void IndexedModel::PushTexCoords(Vector4f vector) {
    m_texCoords.push_back(vector);
}
void IndexedModel::PushNormal(Vector4f vector) {
    m_normals.push_back(vector);
}
void IndexedModel::PushTangent(Vector4f vector) {
    m_tangents.push_back(vector);
}
void IndexedModel:: PushIndice(int index) {
    m_indices.push_back(index);
}

void IndexedModel::SetPositions(std::vector <Vector4f> vectors) {
    m_positions = vectors;
}
void IndexedModel::SetTexCoords(std::vector <Vector4f> vectors) {
    m_texCoords = vectors;
}
void IndexedModel::SetNormals(std::vector <Vector4f> vectors) {
    m_normals = vectors;
}
void IndexedModel::SetTangents(std::vector <Vector4f> vectors) {
    m_tangents = vectors;
}
void IndexedModel::SetIndices(std::vector <int> indexes) {
    m_indices = indexes;
}


