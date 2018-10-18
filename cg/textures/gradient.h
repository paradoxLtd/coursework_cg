#ifndef GRADIENT_H
#define GRADIENT_H

#include <QColor>
#include <vector>
#include "vector.h"
#include "assert.h"
//#include "drawer.h"
#include "vertex.h"

class Gradient
{
public:
    Gradient() = delete;
    Gradient(Vertex minYVert, Vertex middleYVert, Vertex maxYVert);

    Vector get_color_idx(int idx);

    Vector get_color_x_step();
    Vector get_color_y_step();
    float GetDepth(int ind);
    float GetDepthXStep();
    float GetDepthYStep();

private:
    std::vector <Vector> m_color;
    std::vector <float> m_depth;
    float m_depthXStep;
    float m_depthYStep;
    Vector color_x_step;
    Vector color_y_step;

    float CalcXStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
            Vertex maxYVert, float dX);

    float CalcYStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
            Vertex maxYVert, float dY);


};

#endif // GRADIENT_H
