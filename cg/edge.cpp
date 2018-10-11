#include "edge.h"

Edge::Edge(Gradient gr, Vertex minYPoint, Vertex maxYPoint, int min_idx)
{
    y_start = static_cast<int> (std::ceil(minYPoint.y));
    y_end = static_cast<int> (std::ceil(maxYPoint.y));

    assert(y_end >= y_start);

    double y_dst = maxYPoint.y - minYPoint.y;

    //assert(y_dst != 0);

    double x_dst = maxYPoint.x - minYPoint.x;

    double y_prestep = y_start - minYPoint.y;


    if (fabs(y_dst) < 1e-6)
        x_step = 0;
    else
        x_step = x_dst / y_dst;

    x = minYPoint.x + y_prestep * x_step;

    double x_prestep = x - minYPoint.x;

    color = gr.get_color_idx(min_idx) + (gr.get_color_y_step() * y_prestep) + (gr.get_color_x_step() * x_prestep);
    color_step = gr.get_color_y_step() + (gr.get_color_x_step() * x_step);
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

void Edge::step()
{
    x += x_step;
    color += color_step;
}

