#include "Options.h"

void Options::init(
        double a,
        double b,
        double c,
        bool inv)
{
    this->params[0] = a;
    this->params[1] = b;
    this->params[2] = c;
    this->inverse = inv;
}

MoveOptions::MoveOptions(double a, double b,
                         double c, bool inv)
{
    init(a, b, c, inv);
}

/*
MoveOptions::MoveOptions(Point *p, bool inv)
{
    init(p->x, p->y, p->z, inv);
}
*/

MoveOptions::MoveOptions(const Point *p, bool inv)
{
    init(p->x, p->y, p->z, inv);
}

ScaleOptions::ScaleOptions(double a,
                           double b,
                           double c,
                           bool inv)
{
    init(a, b, c, inv);
}

RotateOptions::RotateOptions(double a,
                             double b,
                             double c,
                             bool inv)
{
    init(a, b, c, inv);
    /*
    this->params[0] = NOTHING;
    this->params[1] = angle;
    this->params[2] = 0;
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
    */
}

// Переопределение вывода
std::ostream& operator<<
    (std::ostream& os, const MoveOptions& opt)
{
    os << "\n MoveOptions(dx:" << opt[0] <<
          ", dy: " << opt[1] <<
          ", dz: " << opt[2] <<
          ", inverse: ";
    if (opt.inverse)
        os << "true";
    else
        os << "false";
    os << ")\n";
   return os;
}

// Переопределение вывода
std::ostream& operator<<
    (std::ostream& os, const RotateOptions& opt)
{
    os << "\n RotateOptions(rx:" << opt[0] <<
          ", ry: " << opt[1] <<
          ", rz: " << opt[2] <<
          ", inverse: ";
    if (opt.inverse)
        os << "true";
    else
        os << "false";
    os << ")\n";
   return os;
}

// Переопределение вывода
std::ostream& operator<<
    (std::ostream& os, const ScaleOptions& opt)
{
    os << "\n ScaleOptions(sx:" << opt[0] <<
          ", sy: " << opt[1] <<
          ", sz: " << opt[2] <<
          ", inverse: ";
    if (opt.inverse)
        os << "true";
    else
        os << "false";
    os << ")\n";
   return os;
}

