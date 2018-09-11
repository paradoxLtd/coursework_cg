#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


#include "Point.h"
#include "Vector.h"
#include "Options.h"
#include "Matrix.h"
#include <iostream>

#define SIZE 4

class Action
{
public:
    virtual Vector apply(const Vector &v, Options &opt) = 0;
};

class Move : public Action
{
    Vector apply(const Vector &v, Options &opt) override;
};

class Rotate : public Action
{
private:
    Vector rotateX(const Vector &v, double angle);
    Vector rotateY(const Vector &v, double angle);
    Vector rotateZ(const Vector &v, double angle);
public:
    Vector apply(const Vector &v, Options &opt) override;
};

class Scale : public Action
{
    Vector apply(const Vector &v, Options &opt) override;
};

class Transformation
{
public:
    static Vector apply(const Vector &vector,
        Action &act, Options &opt);
    static Point apply(Point &point,
        Action &act, Options &opt);
    static Point apply(const Point &point,
        Action &act, Options &opt);
    static Point fullTransform(Point p, MoveOptions &mop,
                               RotateOptions &rop,
                               ScaleOptions &sop)
    {
        std::cout << "oops";
        return Point();
    }
};

#endif // TRANSFORMATION_H
