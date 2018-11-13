#ifndef EDGE_H
#define EDGE_H
#include "gradient.h"
#include "vertex.h"

class Edge
{
public:
    float GetX() { return m_x; }
    int GetYStart() { return m_yStart; }
    int GetYEnd() { return m_yEnd; }
    float GetTexCoordX() { return m_texCoordX; }
    float GetTexCoordY() { return m_texCoordY; }
    float GetOneOverZ() { return m_oneOverZ; }
    float GetDepth() { return m_depth; }
    float GetLightAmt() { return m_lightAmt; }

    Edge(Gradients gradients, Vertex minYVert, Vertex maxYVert, int minYVertIndex);
    void Step();

private:
    float m_x;
    float m_xStep;
    int m_yStart;
    int m_yEnd;
    float m_texCoordX;
    float m_texCoordXStep;
    float m_texCoordY;
    float m_texCoordYStep;
    float m_oneOverZ;
    float m_oneOverZStep;
    float m_depth;
    float m_depthStep;
    float m_lightAmt;
    float m_lightAmtStep;

};


#endif // EDGE_H
