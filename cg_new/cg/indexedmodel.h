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

    std::vector <Vector4f> getPositions();
    std::vector <Vector4f> getTexCoords();
    std::vector <Vector4f> getNormals();
    std::vector <Vector4f> getTangents();
    std::vector <int> getIndices();


private:
    std::vector <Vector4f> m_positions;
    std::vector <Vector4f> m_texCoords;
    std::vector <Vector4f> m_normals;
    std::vector <Vector4f> m_tangents;
    std::vector <int> m_indices;

};

#endif // INDEXEDMODEL_H
