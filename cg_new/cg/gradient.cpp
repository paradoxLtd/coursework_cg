#include "gradient.h"

Gradients::Gradients(Vertex minYVert, Vertex midYVert,
                     Vertex maxYVert)
{
    float oneOverdX = 1.0f /
        (((midYVert.GetX() - maxYVert.GetX()) *
        (minYVert.GetY() - maxYVert.GetY())) -
        ((minYVert.GetX() - maxYVert.GetX()) *
        (midYVert.GetY() - maxYVert.GetY())));

    float oneOverdY = -oneOverdX;

    m_oneOverZ.resize(3);
    m_texCoordX.resize(3);
    m_texCoordY.resize(3);
    m_depth.resize(3);
    m_lightAmt.resize(3);

    m_depth[0] = minYVert.GetPosition().GetZ();
    m_depth[1] = midYVert.GetPosition().GetZ();
    m_depth[2] = maxYVert.GetPosition().GetZ();

    Vector4f lightDir(0,0,1);
    m_lightAmt[0] = Saturate(minYVert.GetNormal().
                             Dot(lightDir)) * 0.9f + 0.1f;
    m_lightAmt[1] = Saturate(midYVert.GetNormal().
                             Dot(lightDir)) * 0.9f + 0.1f;
    m_lightAmt[2] = Saturate(maxYVert.GetNormal().
                             Dot(lightDir)) * 0.9f + 0.1f;

    // Note that the W component is the perspective Z value;
    // The Z component is the occlusion Z value
    m_oneOverZ[0] = 1.0f/minYVert.GetPosition().GetW();
    m_oneOverZ[1] = 1.0f/midYVert.GetPosition().GetW();
    m_oneOverZ[2] = 1.0f/maxYVert.GetPosition().GetW();

    m_texCoordX[0] = minYVert.GetTexCoords().GetX() *
            m_oneOverZ[0];
    m_texCoordX[1] = midYVert.GetTexCoords().GetX() *
            m_oneOverZ[1];
    m_texCoordX[2] = maxYVert.GetTexCoords().GetX() *
            m_oneOverZ[2];

    m_texCoordY[0] = minYVert.GetTexCoords().GetY() *
            m_oneOverZ[0];
    m_texCoordY[1] = midYVert.GetTexCoords().GetY() *
            m_oneOverZ[1];
    m_texCoordY[2] = maxYVert.GetTexCoords().GetY() *
            m_oneOverZ[2];

    m_texCoordXXStep = CalcXStep(m_texCoordX, minYVert,
                                 midYVert, maxYVert, oneOverdX);
    m_texCoordXYStep = CalcYStep(m_texCoordX, minYVert,
                                 midYVert, maxYVert, oneOverdY);
    m_texCoordYXStep = CalcXStep(m_texCoordY, minYVert,
                                 midYVert, maxYVert, oneOverdX);
    m_texCoordYYStep = CalcYStep(m_texCoordY, minYVert,
                                 midYVert, maxYVert, oneOverdY);
    m_oneOverZXStep = CalcXStep(m_oneOverZ, minYVert,
                                midYVert, maxYVert, oneOverdX);
    m_oneOverZYStep = CalcYStep(m_oneOverZ, minYVert,
                                midYVert, maxYVert, oneOverdY);
    m_depthXStep = CalcXStep(m_depth, minYVert,
                             midYVert, maxYVert, oneOverdX);
    m_depthYStep = CalcYStep(m_depth, minYVert,
                             midYVert, maxYVert, oneOverdY);
    m_lightAmtXStep = CalcXStep(m_lightAmt, minYVert,
                                midYVert, maxYVert, oneOverdX);
    m_lightAmtYStep = CalcYStep(m_lightAmt, minYVert,
                                midYVert, maxYVert, oneOverdY);
}

float Gradients::CalcXStep(std::vector<float> values,
                           Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, float oneOverdX) {
    return
        (((values[1] - values[2]) *
        (minYVert.GetY() - maxYVert.GetY())) -
        ((values[0] - values[2]) *
        (midYVert.GetY() - maxYVert.GetY()))) * oneOverdX;
}

float Gradients::CalcYStep(std::vector<float> values,
                           Vertex minYVert, Vertex midYVert,
                           Vertex maxYVert, float oneOverdY) {
    return
        (((values[1] - values[2]) *
        (minYVert.GetX() - maxYVert.GetX())) -
        ((values[0] - values[2]) *
        (midYVert.GetX() - maxYVert.GetX()))) * oneOverdY;
}

float Gradients::Saturate(float val) {
    if(val > 1.0f) {
        return 1.0f;
    } else if(val < 0.0f) {
        return 0.0f;
    }
    return val;
}


