#include "matrix4f.h"

Matrix4f::Matrix4f()
{
    this->_mtx.resize(4, std::vector<float>(4, 0));
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

Matrix4f Matrix4f::InitScreenSpaceTransform(float halfWidth,
                                            float halfHeight)
{
    this->_mtx = {
        {halfWidth, 0, 0, halfWidth - 0.5f},
        {0, -halfHeight, 0, halfHeight - 0.5f},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitTranslation(float x, float y, float z)
{
    this->_mtx = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitRotation(float x, float y, float z,
                                float angle)
{
    float sinus = sin(angle);
    float cosin = cos(angle);

    this->_mtx = {
        {cosin+x*x*(1-cosin),
         x*y*(1-cosin)-z*sinus,
         x*z*(1-cosin)+y*sinus, 0},
        {y*x*(1-cosin)+z*sinus,
         cosin+y*y*(1-cosin),
         y*z*(1-cosin)-x*sinus,
         0},
        {z*x*(1-cosin)-y*sinus,
         z*y*(1-cosin)+x*sinus,
         cosin+z*z*(1-cosin), 0},
        {0, 0, 0, 1}
    };

    return *this;

}

Matrix4f Matrix4f::InitRotation(float x, float y, float z)
{
    Matrix4f rx;
    Matrix4f ry;
    Matrix4f rz;

    rz.SetMtx({
        {cos(z), -sin(z), 0, 0},
        {sin(z), cos(z), 0, y},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });

    rx.SetMtx({
        {1, 0, 0, 0},
        {0, cos(x), -sin(x), 0},
        {0, sin(x), cos(x), 0},
        {0, 0, 0, 1}
    });

    ry.SetMtx({
        {cos(y), 0, -sin(y), 0},
        {0, 1, 0, 0},
        {sin(y), 0, cos(y), 0},
        {0, 0, 0, 1}
    });

    this->_mtx = rz.Mul(ry.Mul(rx)).GetMtx();

    return *this;
}

Matrix4f Matrix4f::InitRotation(Vector4f forward, Vector4f up)
{
    Vector4f f = forward.Normalized();

    Vector4f r = up.Normalized();
    r = r.Cross(f);

    Vector4f u = f.Cross(r);

    return InitRotation(f, u, r);
}

Matrix4f Matrix4f::InitRotation(Vector4f forward,
                                Vector4f up, Vector4f right)
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

Matrix4f Matrix4f::InitScale(float x, float y, float z)
{
    this->_mtx = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    };

    return *this;
}

Matrix4f Matrix4f::InitPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
    float tanHalfFOV = tan(fov / 2);
    float zRange = zNear - zFar;

    this->_mtx = {
        { 1.f / (tanHalfFOV * aspectRatio), 0, 0, 0},
        { 0, 1.f / tanHalfFOV, 0, 0},
        {0, 0, (-zNear -zFar)/zRange, 2.f * zFar * zNear / zRange},
        {0, 0, 1.f, 0}
    };

    return *this;
}

Matrix4f Matrix4f::InitOrthographic(float left, float right,
                                    float bottom, float top,
                                    float near, float far)
{
    float width = right - left;
    float height = top - bottom;
    float depth = far - near;

    this->_mtx = {
        {2.f / width, 0, 0, -(right + left)/width},
        {0, 2.f / height, 0, -(top + bottom)/height},
        {0, 0, -2.f/depth, -(far + near)/depth},
        {0, 0, 0, 1}
    };

    return *this;
}

#include <QDebug>

Vector4f Matrix4f::Transform(Vector4f r)
{
    Vector4f tmp;
    //qDebug() << "TR befire";
    //qDebug() << r.GetX() << " " << r.GetY() << " " << r.GetZ() <<" " << r.GetW();
    /*tmp = Vector4f(_mtx[0][0] * r.GetX() + _mtx[0][1] * r.GetY() +
            _mtx[0][2] * r.GetZ() + _mtx[0][3] * r.GetW(),

        _mtx[1][0] * r.GetX() + _mtx[1][1] * r.GetY() +
            _mtx[1][2] * r.GetZ() + _mtx[1][3] * r.GetW(),

        _mtx[2][0] * r.GetX() + _mtx[2][1] * r.GetY() +
            _mtx[2][2] * r.GetZ() + _mtx[2][3] * r.GetW(),

        _mtx[3][0] * r.GetX() + _mtx[3][1] * r.GetY() +
            _mtx[3][2] * r.GetZ() + _mtx[3][3] * r.GetW());

    *///qDebug() << "TR after";
    //qDebug() << tmp.GetX() << " " << tmp.GetY() << " " << tmp.GetZ() <<" " << tmp.GetW();
    return Vector4f(_mtx[0][0] * r.GetX() + _mtx[0][1] * r.GetY() +
                        _mtx[0][2] * r.GetZ() + _mtx[0][3] * r.GetW(),

                    _mtx[1][0] * r.GetX() + _mtx[1][1] * r.GetY() +
                        _mtx[1][2] * r.GetZ() + _mtx[1][3] * r.GetW(),

                    _mtx[2][0] * r.GetX() + _mtx[2][1] * r.GetY() +
                        _mtx[2][2] * r.GetZ() + _mtx[2][3] * r.GetW(),

                    _mtx[3][0] * r.GetX() + _mtx[3][1] * r.GetY() +
                        _mtx[3][2] * r.GetZ() + _mtx[3][3] * r.GetW());
}

Matrix4f Matrix4f::Mul(Matrix4f r)
{
    Matrix4f res = Matrix4f();

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            res.Set(i, j, _mtx[i][0] * r.Get(0, j) +
                    _mtx[i][1] * r.Get(1, j) +
                    _mtx[i][2] * r.Get(2, j) +
                    _mtx[i][3] * r.Get(3, j));
        }
    }

    return res;
}

std::vector<std::vector<float> > Matrix4f::GetMtx()
{
    return this->_mtx;
}

void Matrix4f::SetMtx(std::vector<std::vector<float>> mtx)
{
    this->_mtx = mtx;
}

float Matrix4f::Get(int x, int y)
{
    return this->_mtx[x][y];
}

void Matrix4f::Set(int x, int y, float value)
{
    this->_mtx[x][y] = value;
}
