#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <vector>
#include <cmath>
#include "vector4f.h"

class Matrix4f
{
public:
    Matrix4f();
    Matrix4f InitIdentity();
    Matrix4f InitScreenSpaceTransform(double halfWidth, double halfHeight);
    Matrix4f InitTranslation(double x, double y, double z);
    Matrix4f InitRotation(double x, double y, double z, double angle);
    Matrix4f InitRotation(double x, double y, double z);

    Matrix4f InitRotation(Vector4f forward, Vector4f up);
    Matrix4f InitRotation(Vector4f forward, Vector4f up, Vector4f right);


    Matrix4f InitScale(double x, double y, double z);
    Matrix4f InitPerspective(double fov, double aspectRatio,
                             double zNear, double zFar);
    Matrix4f InitOrthographic(double left, double right,
                              double bottom, double top,
                              double near, double far);

    Vector4f Transform(Vector4f r);
    Matrix4f Mul(Matrix4f r);

    std::vector <std::vector <double>> GetMtx();
    void SetMtx(std::vector <std::vector <double>> mtx);


    double Get(int x, int y);
    void Set(int x, int y, double value);


private:
    std::vector <std::vector <double>> _mtx;

};

#endif // MATRIX4F_H
