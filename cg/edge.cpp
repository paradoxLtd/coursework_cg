#include "edge.h"
#include <qDebug>

Edge::Edge(Gradient gr, Vertex minYPoint, Vertex maxYPoint, int min_idx)
{
    y_start = static_cast<int> (std::ceil(minYPoint.GetY()));
    y_end = static_cast<int> (std::ceil(maxYPoint.GetY()));


    assert(y_end >= y_start);

    double y_dst = maxYPoint.GetY() - minYPoint.GetY();

    //assert(y_dst != 0);

    double x_dst = maxYPoint.GetX() - minYPoint.GetX();

    double y_prestep = y_start - minYPoint.GetY();


    if (fabs(y_dst) < 1e-6)
        x_step = 0.;
    else
        x_step = x_dst / y_dst;

    x = minYPoint.GetX() + y_prestep * x_step;

    double x_prestep = x - minYPoint.GetX();

    color = gr.get_color_idx(min_idx) + (gr.get_color_y_step() * y_prestep) + (gr.get_color_x_step() * x_prestep);
    color_step = gr.get_color_y_step() + (gr.get_color_x_step() * x_step);


    m_texCoordX = gr.GetTexCoordX(min_idx) +
        gr.GetTexCoordXXStep() * x_prestep +
        gr.GetTexCoordXYStep() * y_prestep;
    m_texCoordXStep = gr.GetTexCoordXYStep() + gr.GetTexCoordXXStep() * x_step;

    m_texCoordY = gr.GetTexCoordY(min_idx) +
        gr.GetTexCoordYXStep() * x_prestep +
        gr.GetTexCoordYYStep() * y_prestep;
    m_texCoordYStep = gr.GetTexCoordYYStep() + gr.GetTexCoordYXStep() * x_step;


    m_oneOverZ = gr.GetOneOverZ(min_idx) +
                gr.GetOneOverZXStep() * x_prestep +
                gr.GetOneOverZYStep() * y_prestep;
    m_oneOverZStep = gr.GetOneOverZYStep() + gr.GetOneOverZXStep() * x_step;

    m_depth = gr.GetDepth(min_idx) +
                gr.GetDepthXStep() * x_prestep +
                gr.GetDepthYStep() * y_prestep;
    m_depthStep = gr.GetDepthYStep() + gr.GetDepthXStep() * x_step;
}


double Edge::get_x()
{
    return this->x;
}

int Edge::get_y_start()
{
    return this->y_start;
}

int Edge::get_y_end()
{
    return this->y_end;
}

Vector Edge::get_color()
{
    return  this->color;
}

void Edge::set_x(double x)
{
    this->x = x;
}

void Edge::step()
{
    x += x_step;
    m_texCoordX += m_texCoordXStep;
    m_texCoordY += m_texCoordYStep;
    color += color_step;
    m_depth += m_depthStep;
    m_oneOverZ += m_oneOverZStep;
}

float Edge::getDepth()
{
    return m_depth;
}

