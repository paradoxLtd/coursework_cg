#include "gradient.h"

#include <qDebug>
Gradient::Gradient(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint)
{
    m_color.push_back(minYPoint.get_p_color());
    m_color.push_back(middleYPoint.get_p_color());
    m_color.push_back(maxYPoint.get_p_color());

    double oneOverdX = 1.0 / ( ( (middleYPoint.x - maxYPoint.x) * (minYPoint.y - maxYPoint.y)) -
                               ( (minYPoint.x - maxYPoint.x) * (middleYPoint.y - maxYPoint.y) ) );

    double oneOverdY = -oneOverdX;

    m_color_x_step = ((m_color[1] - m_color[2]) * (minYPoint.y - maxYPoint.y) - (m_color[0] - m_color[2]) *
            (middleYPoint.y - maxYPoint.y)) * oneOverdX;
    m_color_y_step = ((m_color[1] - m_color[2]) * (minYPoint.x - maxYPoint.x) - (m_color[0] - m_color[2]) *
            (middleYPoint.x - maxYPoint.x)) * oneOverdY;

    qDebug() << "M_COLOR_STEP " << m_color_x_step.x << " " << m_color_x_step.y << " " << m_color_x_step.z;
}

Vector Gradient::get_color_idx(int idx)
{
    assert(idx >= 0 && idx <= 2);
    return m_color[idx];
}

Vector Gradient::get_color_x_step()
{
    return this->m_color_x_step;
}

Vector Gradient::get_color_y_step()
{
    return this->m_color_y_step;
}
