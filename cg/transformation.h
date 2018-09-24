#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Camera;

#include "point.h"
#include "vector.h"
#include "options.h"
#include "matrix.h"
#include "object.h"
#include "camera.h"

#include <iostream>

#define SIZE 4

class Action
{
public:
    virtual Vector apply(
            const Vector &v,
            const Options &opt) const = 0;
    virtual void apply(
            Camera &cam,
            const Options &opt) const = 0;
    virtual void apply(
            Object &obj,
            const Options &opt) const = 0;
};

class Move : public Action
{
    Vector apply(
            const Vector &v,
            const Options &opt) const override;
    void apply(
            Camera &cam,
            const Options &opt) const override;
    void apply(
            Object &obj,
            const Options &opt) const override;
};

class Rotate : public Action
{
private:
    Vector rotateX(const Vector &v, double angle) const;
    Vector rotateY(const Vector &v, double angle) const;
    Vector rotateZ(const Vector &v, double angle) const;
public:
    Vector apply(
            const Vector &v,
            const Options &opt) const override;
    void apply(
            Camera &cam,
            const Options &opt) const override;
    void apply(
            Object &obj,
            const Options &opt) const override;
};

class Scale : public Action
{
    Vector apply(
            const Vector &v,
            const Options &opt) const override;
    void apply(
            Camera &cam,
            const Options &opt) const override;
    void apply(
            Object &obj,
            const Options &opt) const override;
};

class Transformation
{
public:
    static Vector transform(const Vector &vector,
        const Action &act, const Options &opt);
    static Point transform(const Point &point,
        const Action &act, const Options &opt);
    static void transform(Camera &cam,
                          const Action &act,
                          const Options &opt);
    static void transform(Object &object,
                          const Action &act,
                          const Options &opt);

    static void fullTransform(Object &object, MoveOptions &mop,
                               RotateOptions &rop,
                               ScaleOptions &sop);
    static void fullTransform(Camera &cam, MoveOptions &mop,
                               RotateOptions &rop,
                               ScaleOptions &sop);
};

#endif // TRANSFORMATION_H
