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

private:
    std::vector <Vector> m_color;

    Vector color_x_step;
    Vector color_y_step;


};

#endif // GRADIENT_H
