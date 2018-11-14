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

    Edge(const Edge &other) {
        this->m_x = other.m_x;
        this->m_xStep = other.m_xStep;
        this->m_yStart = other.m_yStart;
        this->m_yEnd = other.m_yEnd;
        this->m_texCoordX = other.m_texCoordX;
        this->m_texCoordXStep = other.m_texCoordXStep;
        this->m_texCoordY = other.m_texCoordY;
        this->m_texCoordYStep = other.m_texCoordYStep;
        this->m_oneOverZ = other.m_oneOverZ;
        this->m_oneOverZStep = other.m_oneOverZStep;
        this->m_depth = other.m_depth;
        this->m_depthStep = other.m_depthStep;
        this->m_lightAmt = other.m_lightAmt;
        this->m_lightAmtStep = other.m_lightAmtStep;
    }

    Edge(Edge &&other) {
        this->m_x = other.m_x;
        this->m_xStep = other.m_xStep;
        this->m_yStart = other.m_yStart;
        this->m_yEnd = other.m_yEnd;
        this->m_texCoordX = other.m_texCoordX;
        this->m_texCoordXStep = other.m_texCoordXStep;
        this->m_texCoordY = other.m_texCoordY;
        this->m_texCoordYStep = other.m_texCoordYStep;
        this->m_oneOverZ = other.m_oneOverZ;
        this->m_oneOverZStep = other.m_oneOverZStep;
        this->m_depth = other.m_depth;
        this->m_depthStep = other.m_depthStep;
        this->m_lightAmt = other.m_lightAmt;
        this->m_lightAmtStep = other.m_lightAmtStep;
    }

    Edge operator=
    (const Edge& other) {
        this->m_x = other.m_x;
        this->m_xStep = other.m_xStep;
        this->m_yStart = other.m_yStart;
        this->m_yEnd = other.m_yEnd;
        this->m_texCoordX = other.m_texCoordX;
        this->m_texCoordXStep = other.m_texCoordXStep;
        this->m_texCoordY = other.m_texCoordY;
        this->m_texCoordYStep = other.m_texCoordYStep;
        this->m_oneOverZ = other.m_oneOverZ;
        this->m_oneOverZStep = other.m_oneOverZStep;
        this->m_depth = other.m_depth;
        this->m_depthStep = other.m_depthStep;
        this->m_lightAmt = other.m_lightAmt;
        this->m_lightAmtStep = other.m_lightAmtStep;
        return *this;
    }

    Edge operator=
    (Edge&& other) {
        this->m_x = other.m_x;
        this->m_xStep = other.m_xStep;
        this->m_yStart = other.m_yStart;
        this->m_yEnd = other.m_yEnd;
        this->m_texCoordX = other.m_texCoordX;
        this->m_texCoordXStep = other.m_texCoordXStep;
        this->m_texCoordY = other.m_texCoordY;
        this->m_texCoordYStep = other.m_texCoordYStep;
        this->m_oneOverZ = other.m_oneOverZ;
        this->m_oneOverZStep = other.m_oneOverZStep;
        this->m_depth = other.m_depth;
        this->m_depthStep = other.m_depthStep;
        this->m_lightAmt = other.m_lightAmt;
        this->m_lightAmtStep = other.m_lightAmtStep;
        return *this;
    }

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
