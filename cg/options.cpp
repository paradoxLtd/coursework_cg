#include "Options.h"

MoveOptions::MoveOptions()
{
    this->params[0] = 0;
    this->params[1] = 0;
    this->params[2] = 0;
    this->inverse = false;
}

MoveOptions::MoveOptions(Point *p, bool inv)
{
    this->params[0] = p->x;
    this->params[1] = p->y;
    this->params[2] = p->z;
    this->inverse = inv;
}

ScaleOptions::ScaleOptions()
{
    this->params[0] = 1;
    this->params[1] = 1;
    this->params[2] = 1;
    this->inverse = false;
}

RotateOptions::RotateOptions()
{
    this->params[0] = NOTHING;
    this->params[1] = 0;
    this->params[2] = 0;
    this->inverse = false;
}

RotateOptions::RotateOptions(int choose, double angle, bool in)
{
    this->params[2] = 0;
    this->params[1] = angle;
    this->params[0] = NOTHING;
    switch (choose)
    {
    case AXIS_X:
    {
        this->params[0] = AXIS_X;
        break;
    }
    case AXIS_Y:
    {
        this->params[0] = AXIS_Y;
        break;
    }
    case AXIS_Z:
    {
        this->params[0] = AXIS_Z;
        break;
    }
    default:
        std::cout << "Указана несуществующая ось поворота" << choose;
        this->params[1] = 0;
    }
    this->inverse = in;
}
