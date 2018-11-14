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
    Matrix4f InitScreenSpaceTransform(float halfWidth, float halfHeight);
    Matrix4f InitTranslation(float x, float y, float z);
    Matrix4f InitRotation(float x, float y, float z, float angle);
    Matrix4f InitRotation(float x, float y, float z);

    Matrix4f InitRotation(Vector4f forward, Vector4f up);
    Matrix4f InitRotation(Vector4f forward, Vector4f up, Vector4f right);


    Matrix4f InitScale(float x, float y, float z);
    Matrix4f InitPerspective(float fov, float aspectRatio,
                             float zNear, float zFar);
    Matrix4f InitOrthographic(float left, float right,
                              float bottom, float top,
                              float near, float far);

    Vector4f Transform(Vector4f r);
    Matrix4f Mul(Matrix4f r);

    std::vector <std::vector <float>> GetMtx();
    void SetMtx(std::vector <std::vector <float>> mtx);


    float Get(int x, int y);
    void Set(int x, int y, float value);


private:
    std::vector <std::vector <float>> _mtx;

};

#endif // MATRIX4F_H
