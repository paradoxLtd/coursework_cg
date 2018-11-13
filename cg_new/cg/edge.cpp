#include "edge.h"
#include <cmath>

Edge::Edge(Gradients gradients, Vertex minYVert, Vertex maxYVert, int minYVertIndex)
{
    m_yStart = (int)ceil(minYVert.GetY());
    m_yEnd = (int)ceil(maxYVert.GetY());

    float yDist = maxYVert.GetY() - minYVert.GetY();
    float xDist = maxYVert.GetX() - minYVert.GetX();

    float yPrestep = m_yStart - minYVert.GetY();
    m_xStep = (float)xDist/(float)yDist;
    m_x = minYVert.GetX() + yPrestep * m_xStep;
    float xPrestep = m_x - minYVert.GetX();

    m_texCoordX = gradients.GetTexCoordX(minYVertIndex) +
        gradients.GetTexCoordXXStep() * xPrestep +
        gradients.GetTexCoordXYStep() * yPrestep;
    m_texCoordXStep = gradients.GetTexCoordXYStep() + gradients.GetTexCoordXXStep() * m_xStep;

    m_texCoordY = gradients.GetTexCoordY(minYVertIndex) +
        gradients.GetTexCoordYXStep() * xPrestep +
        gradients.GetTexCoordYYStep() * yPrestep;
    m_texCoordYStep = gradients.GetTexCoordYYStep() + gradients.GetTexCoordYXStep() * m_xStep;

    m_oneOverZ = gradients.GetOneOverZ(minYVertIndex) +
        gradients.GetOneOverZXStep() * xPrestep +
        gradients.GetOneOverZYStep() * yPrestep;
    m_oneOverZStep = gradients.GetOneOverZYStep() + gradients.GetOneOverZXStep() * m_xStep;

    m_depth = gradients.GetDepth(minYVertIndex) +
        gradients.GetDepthXStep() * xPrestep +
        gradients.GetDepthYStep() * yPrestep;
    m_depthStep = gradients.GetDepthYStep() + gradients.GetDepthXStep() * m_xStep;

    m_lightAmt = gradients.GetLightAmt(minYVertIndex) +
        gradients.GetLightAmtXStep() * xPrestep +
        gradients.GetLightAmtYStep() * yPrestep;
    m_lightAmtStep = gradients.GetLightAmtYStep() + gradients.GetLightAmtXStep() * m_xStep;
}

void Edge::Step()
{
    m_x += m_xStep;
    m_texCoordX += m_texCoordXStep;
    m_texCoordY += m_texCoordYStep;
    m_oneOverZ += m_oneOverZStep;
    m_depth += m_depthStep;
    m_lightAmt += m_lightAmtStep;
}
