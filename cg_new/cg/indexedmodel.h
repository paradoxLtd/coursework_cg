#ifndef INDEXEDMODEL_H
#define INDEXEDMODEL_H

#include <vector>
#include "vector4f.h"

class IndexedModel
{
public:
    IndexedModel() = default;

    void calcNormals();
    void calcTangents();

    std::vector <Vector4f> GetPositions() const;
    std::vector <Vector4f> GetTexCoords() const;
    std::vector <Vector4f> GetNormals() const;
    std::vector <Vector4f> GetTangents() const;
    std::vector <int> GetIndices() const;

    // Добаваить 1 элемент в любой из векторов
    void PushPosition(Vector4f vector);
    void PushTexCoords(Vector4f vector);
    void PushNormal(Vector4f vector);
    void PushTangent(Vector4f vector);
    void PushIndice(int index);

    // Заменить вектор на новый
    void SetPositions(std::vector <Vector4f> vectors);
    void SetTexCoords(std::vector <Vector4f> vectors);
    void SetNormals(std::vector <Vector4f> vectors);
    void SetTangents(std::vector <Vector4f> vectors);
    void SetIndices(std::vector <int> indexes);


private:
    std::vector <Vector4f> m_positions;
    std::vector <Vector4f> m_texCoords;
    std::vector <Vector4f> m_normals;
    std::vector <Vector4f> m_tangents;
    std::vector <int> m_indices;

};

#endif // INDEXEDMODEL_H
