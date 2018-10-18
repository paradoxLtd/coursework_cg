#include "gradient.h"

#include <qDebug>

float Gradient::CalcXStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, float dX)
{
    return
        (((values[1] - values[2]) *
        (minYVert.y - maxYVert.y)) -
        ((values[0] - values[2]) *
        (midYVert.y - maxYVert.y))) * dX;
}

float Gradient::CalcYStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, float dY)
{
    return
        (((values[1] - values[2]) *
        (minYVert.x - maxYVert.x)) -
        ((values[0] - values[2]) *
        (midYVert.x - maxYVert.x))) * dY;
}

Gradient::Gradient(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint)
{
    m_color.push_back(minYPoint.get_p_color());
    m_color.push_back(middleYPoint.get_p_color());
    m_color.push_back(maxYPoint.get_p_color());

    /*qDebug() << "COLORRRRS";
    qDebug() << m_color[0].x << " " << m_color[0].y << " " << m_color[0].z;
    qDebug() << m_color[1].x << " " << m_color[1].y << " " << m_color[1].z;
    qDebug() << m_color[2].x << " " << m_color[2].y << " " << m_color[2].z;*/

    float dx = 1.0f/((middleYPoint.x - maxYPoint.x) *
                     (minYPoint.y - maxYPoint.y) +
                     (maxYPoint.x - minYPoint.x) *
                     (middleYPoint.y - maxYPoint.y));

    color_x_step = ((m_color[1] - m_color[2]) *
            (minYPoint.y  - maxYPoint.y) +
            (m_color[2] -m_color[0]) *
            (middleYPoint.y - maxYPoint.y)) * dx;


    float dy = -dx;
    //double dy = (minYPoint.x - maxYPoint.x) * (middleYPoint.y - maxYPoint.y) - (middleYPoint.x - maxYPoint.x) * (minYPoint.y - maxYPoint.y);

    color_y_step = ((m_color[1] - m_color[2]) *
            (minYPoint.x - maxYPoint.x) -
            (m_color[0] - m_color[2]) *
            (middleYPoint.x - maxYPoint.x)) * dy;

    m_depth.push_back(minYPoint.z);
    m_depth.push_back(middleYPoint.z);
    m_depth.push_back(maxYPoint.z);

    m_depthXStep = CalcXStep(m_depth, minYPoint, middleYPoint, maxYPoint, dx);
    m_depthYStep = CalcYStep(m_depth, minYPoint, middleYPoint, maxYPoint, dy);


    /*qDebug() << "COLORRRRS";
    qDebug() << m_color[0].x << " " << m_color[0].y << " " << m_color[0].z;
    qDebug() << m_color[1].x << " " << m_color[1].y << " " << m_color[1].z;
    qDebug() << m_color[2].x << " " << m_color[2].y << " " << m_color[2].z;
    qDebug() << "M_COLOR_XSTEP " << color_x_step.x << " " << color_x_step.y << " " << color_x_step.z;
    qDebug() << dy;
    qDebug() << "M_COLOR_YSTEP " << color_y_step.x << " " << color_y_step.y << " " << color_y_step.z;*/
    //qDebug() << "M_COLOR_XSTEP " << m_color_x_step.x << " " << m_color_x_step.y << " " << m_color_x_step.z;
    //qDebug() << "M_COLOR_YSTEP " << m_color_y_step.x << " " << m_color_y_step.y << " " << m_color_y_step.z;
}


Vector Gradient::get_color_idx(int idx)
{
    assert(idx >= 0 && idx <= 2);
    return m_color[idx];
}

Vector Gradient::get_color_x_step()
{
    return this->color_x_step;
}

Vector Gradient::get_color_y_step()
{
    return this->color_y_step;
}

float Gradient::GetDepth(int ind)
{
    return m_depth[ind];
}

float Gradient::GetDepthXStep()
{
    return m_depthXStep;
}

float Gradient::GetDepthYStep()
{
    return m_depthYStep;
}

