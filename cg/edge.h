#ifndef EDGE_H
#define EDGE_H

#include <cmath>
#include "point.h"
#include "textures/gradient.h"
#include "vertex.h"

class Edge
{
public:
    Edge() = delete;

    Edge(Gradient gr, Vertex minYPoint, Vertex maxYPoint, int min_idx);

    double get_x();
    int get_y_start();
    int get_y_end();
    Vector get_color();

    void step();

private:
    double x;
    double x_step;

    //double y_start;
    //double y_end;

    int y_start;
    int y_end;

    Vector color;
    Vector color_step;


};

#endif // EDGE_H
