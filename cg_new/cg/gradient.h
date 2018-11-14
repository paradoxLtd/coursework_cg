#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include "vertex.h"

class Gradients
{
    Gradients(Vertex minYVert, Vertex midYVert, Vertex maxYVert);

    float GetTexCoordX(int loc) { return m_texCoordX[loc]; }
    float GetTexCoordY(int loc) { return m_texCoordY[loc]; }
    float GetOneOverZ(int loc) { return m_oneOverZ[loc]; }
    float GetDepth(int loc) { return m_depth[loc]; }
    float GetLightAmt(int loc) { return m_lightAmt[loc]; }

    float GetTexCoordXXStep() { return m_texCoordXXStep; }
    float GetTexCoordXYStep() { return m_texCoordXYStep; }
    float GetTexCoordYXStep() { return m_texCoordYXStep; }
    float GetTexCoordYYStep() { return m_texCoordYYStep; }
    float GetOneOverZXStep() { return m_oneOverZXStep; }
    float GetOneOverZYStep() { return m_oneOverZYStep; }
    float GetDepthXStep() { return m_depthXStep; }
    float GetDepthYStep() { return m_depthYStep; }
    float GetLightAmtXStep() { return m_lightAmtXStep; }
    float GetLightAmtYStep() { return m_lightAmtYStep; }

    float CalcXStep(std::vector<float> values, Vertex minYVert, Vertex midYVert, Vertex maxYVert, float oneOverdX);

    float CalcYStep(std::vector<float> values, Vertex minYVert, Vertex midYVert, Vertex maxYVert, float oneOverdY);

    float Saturate(float val);



private:
    std::vector<float> m_texCoordX;
    std::vector<float> m_texCoordY;
    std::vector<float> m_oneOverZ;
    std::vector<float> m_depth;
    std::vector<float> m_lightAmt;
    float m_texCoordXXStep;
    float m_texCoordXYStep;
    float m_texCoordYXStep;
    float m_texCoordYYStep;
    float m_oneOverZXStep;
    float m_oneOverZYStep;
    float m_depthXStep;
    float m_depthYStep;
    float m_lightAmtXStep;
    float m_lightAmtYStep;
};


#endif // GRADIENT_H
