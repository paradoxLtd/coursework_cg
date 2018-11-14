#include "matrix4f.h"

Matrix4f::Matrix4f()
{
    this->_mtx = std::vector<std::vector<double> >(4, vector<char>(4));
}

Matrix4f Matrix4f::InitIdentity()
{
    this->_mtx = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitScreenSpaceTransform(double halfWidth, double halfHeight)
{
    this->_mtx = {
        {halfWidth, 0, 0, halfWidth - 0.5},
        {0, -halfHeight, 0, halfHeight - 0.5},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitTranslation(double x, double y, double z)
{
    this->_mtx = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitRotation(double x, double y, double z, double angle)
{
    double sin = sin(angle);
    double cos = cos(angle);

    this->_mtx = {
        {cos+x*x*(1-cos), x*y*(1-cos)-z*sin, x*z*(1-cos)+y*sin, 0},
        {y*x*(1-cos)+z*sin, cos+y*y*(1-cos), y*z*(1-cos)-x*sin, 0},
        {z*x*(1-cos)-y*sin, z*y*(1-cos)+x*sin, cos+z*z*(1-cos), 0},
        {0, 0, 0, 1}
    };

    return *this;

}

Matrix4f Matrix4f::InitRotation(double x, double y, double z)
{
    Matrix4f rx = Matrix4f();
    Matrix4f ry = Matrix4f();
    Matrix4f rz = Matrix4f();

    rz = {
        {cos(z), -sin(z), 0, 0},
        {sin(z), cos(z), 0, y},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    rx = {
        {1, 0, 0, 0},
        {0, cos(x), -sin(x), 0},
        {0, sin(x), cos(x), 0},
        {0, 0, 0, 1}
    };

    ry = {
        {cos(y), 0, -sin(y), 0},
        {0, 1, 0, 0},
        {sin(y), 0, cos(y), 0},
        {0, 0, 0, 1}
    };

    m = rz.Mul(ry.Mul(rx)).getMtx();

    return *this;
}

Matrix4f Matrix4f::InitRotation(Vector4f &forward, Vector4f &up)
{
    Vector4f f = forward.Normalized();

    Vector4f r = up.Normalized();
    r = r.Cross(f);

    Vector4f u = f.Cross(r);

    return InitRotation(f, u, r);
}

Matrix4f Matrix4f::InitRotation(Vector4f &forward, Vector4f &up, Vector4f &right)
{
    Vector4f f = forward;
    Vector4f r = right;
    Vector4f u = up;

    this->_mtx = {
        {r.GetX(), r.GetY(), r.GetZ(), 0},
        {u.GetX(), u.GetY(), u.GetZ(), 0},
        {f.GetX(), f.GetY(), f.GetZ(), 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitScale(double x, double y, double z)
{
    this->_mtx = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitPerspective(double fov, double aspectRatio, double zNear, double zFar)
{
    double tanHalfFOV = tan(fov / 2);
    double zRange = zNear - zFar;

    this->_mtx = {
        { 1. / (tanHalfFOV * aspectRatio), 0, 0, 0},
        { 0, 1. / tanHalfFOV, 0, 0},
        {0, 0, (-zNear -zFar)/zRange, 2 * zFar * zNear / zRange},
        {0, 0, 1, 0}
    };

    return *this;
}

Matrix4f Matrix4f::InitOrthographic(double left, double right, double bottom, double top, double near, double far)
{
    double width = right - left;
    double height = top - bottom;
    double depth = far - near;

    this->_mtx = {
        {2. / width, 0, 0, -(right + left)/width},
        {0, 2. / height, 0, -(top + bottom)/height},
        {0, 0, -2/depth, -(far + near)/depth},
        {0, 0, 0, 1}
    };

    return *this;
}

Vector4f Matrix4f::Transform(Vector4f &r)
{
    return Vector4f(_mtx[0][0] * r.GetX() + _mtx[0][1] * r.GetY() + _mtx[0][2] * r.GetZ() + _mtx[0][3] * r.GetW(),
                        _mtx[1][0] * r.GetX() + _mtx[1][1] * r.GetY() + _mtx[1][2] * r.GetZ() + _mtx[1][3] * r.GetW(),
                        _mtx[2][0] * r.GetX() + _mtx[2][1] * r.GetY() + _mtx[2][2] * r.GetZ() + _mtx[2][3] * r.GetW(),
            _mtx[3][0] * r.GetX() + _mtx[3][1] * r.GetY() + _mtx[3][2] * r.GetZ() + _mtx[3][3] * r.GetW());
}

Matrix4f Matrix4f::Mul(Matrix4f &r)
{
    Matrix4f res = Matrix4f();

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            res.set(i, j, _mtx[i][0] * r.get(0, j) +
                    _mtx[i][1] * r.get(1, j) +
                    _mtx[i][2] * r.get(2, j) +
                    _mtx[i][3] * r.get(3, j));
        }
    }

    return res;
}

std::vector<std::vector<double> > Matrix4f::getMtx()
{
    return this->_mtx;
}

void Matrix4f::setMtx(std::vector<std::vector<double> > mtx)
{
    this->_mtx = mtx;
}

double Matrix4f::get(int x, int y)
{
    return this->_mtx[x][y];
}

void Matrix4f::set(int x, int y, double value)
{
    this->_mtx[x][y] = value;
}