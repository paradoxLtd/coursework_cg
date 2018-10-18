#include "gradient.h"

#include <qDebug>

float Gradient::CalcXStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, float dX)
{
    return
        (((values[1] - values[2]) *
        (minYVert.GetY() - maxYVert.GetY())) -
        ((values[0] - values[2]) *
        (midYVert.GetY() - maxYVert.GetY()))) * dX;
}

float Gradient::CalcYStep(std::vector<float> values, Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, float dY)
{
    return
        (((values[1] - values[2]) *
        (minYVert.GetX() - maxYVert.GetX())) -
        ((values[0] - values[2]) *
        (midYVert.GetX() - maxYVert.GetX()))) * dY;
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

    float dx = 1.0f/((middleYPoint.GetX() - maxYPoint.GetX()) *
                     (minYPoint.GetY() - maxYPoint.GetY()) +
                     (maxYPoint.GetX() - minYPoint.GetX()) *
                     (middleYPoint.GetY() - maxYPoint.GetY()));

    /*color_x_step = ((m_color[1] - m_color[2]) *
            (minYPoint.y  - maxYPoint.y) +
            (m_color[2] -m_color[0]) *
            (middleYPoint.y - maxYPoint.y)) * dx;*/


    float dy = -dx;
    //double dy = (minYPoint.x - maxYPoint.x) * (middleYPoint.y - maxYPoint.y) - (middleYPoint.x - maxYPoint.x) * (minYPoint.y - maxYPoint.y);

    /*color_y_step = ((m_color[1] - m_color[2]) *
            (minYPoint.x - maxYPoint.x) -
            (m_color[0] - m_color[2]) *
            (middleYPoint.x - maxYPoint.x)) * dy;*/



    m_texCoordX.resize(3);
    m_texCoordY.resize(3);

    m_texCoordX[0] = minYPoint.GetTexCoords().x;
    m_texCoordX[1] = middleYPoint.GetTexCoords().x;
    m_texCoordX[2] = maxYPoint.GetTexCoords().x;

    m_texCoordY[0] = minYPoint.GetTexCoords().y;
    m_texCoordY[1] = middleYPoint.GetTexCoords().y;
    m_texCoordY[2] = maxYPoint.GetTexCoords().z;

    m_texCoordXXStep = CalcXStep(m_texCoordX, minYPoint, middleYPoint, maxYPoint, dx);

    m_texCoordXYStep = CalcYStep(m_texCoordX, minYPoint, middleYPoint, maxYPoint, dy);;

    m_texCoordYXStep = CalcXStep(m_texCoordY, minYPoint, middleYPoint, maxYPoint, dx);

    m_texCoordYYStep = CalcYStep(m_texCoordY, minYPoint, middleYPoint, maxYPoint, dy);

    qDebug() << "kjljljpk "<< m_texCoordXXStep << " " << m_texCoordXYStep;
    m_depth.push_back(minYPoint.GetZ());
    m_depth.push_back(middleYPoint.GetZ());
    m_depth.push_back(maxYPoint.GetZ());

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

