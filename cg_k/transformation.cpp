#include "transformation.h"
#include <cmath>


/*Преобразования*/
Vector Move::apply(const Vector &vector, Options &opt)
{
    double x = opt[0], y = opt[1], z = opt[2];
    if (opt.inverse)
    {
        x *= -1; y *= -1; z *= -1;
    }

    double move_matrix[SIZE][SIZE] =
    {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 }
    };

    return Vector(Matrix::multiplicate(vector, move_matrix));
}

Vector Scale::apply(const Vector &vector, Options &opt)
{
    double x = opt[0], y = opt[1], z = opt[2];
    if (opt.inverse)
    {
        x = 1/x; y = 1/y; z = 1/z;
    }

    double scale_matrix[SIZE][SIZE] =
    {
        { x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 }
    };

    return Vector(Matrix::multiplicate(vector, scale_matrix));
}

Vector Rotate::rotateX(const Vector &vector, double angle)
{
    double rotate_matrix[SIZE][SIZE] =
    {
        { 1,	0,				0,			0 },
        { 0,	cos(angle),		sin(angle), 0 },
        { 0,	-sin(angle),	cos(angle), 0 },
        { 0,	 0,				0,			1 }
    };
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::rotateY(const Vector &vector, double angle)
{
    double rotate_matrix[SIZE][SIZE] =
    {
        { cos(angle), 0,	 -sin(angle), 0 },
        { 0,		  1,	 0,			  0 },
        { sin(angle), 0,	 cos(angle),  0 },
        { 0,		  0,	 0,			  1 }
    };
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::rotateZ(const Vector &vector, double angle)
{
    double rotate_matrix[SIZE][SIZE] =
    {
        {  cos(angle), sin(angle), 0, 0 },
        { -sin(angle), cos(angle), 0, 0 },
        { 0,		   0,		   1, 0 },
        { 0,		   0,		   0, 1 }
    };
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::apply(const Vector &vector, Options &opt){
    int choose = (int)opt[0];
    double angle = opt[1];
    if (opt.inverse)
        angle *= -1;
    Vector v;

    switch (choose)
    {
    case AXIS_X:
    {
        v = rotateX(vector, angle);
        break;
    }
    case AXIS_Y:
    {
        v = rotateY(vector, angle);
        break;
    }
    case AXIS_Z:
    {
        v = rotateZ(vector, angle);
        break;
    }
    }
    return v;
}

/*Преобразования над конкретными объектами*/

/*Как на мой взгляд стоит производить преобразования
К перемещениям стоит добавить также перенос center, а также
векторов dir, ux, uy, и uz

В случае поворотов мы получаем приращение для нашего вектора
dir, соответственно под него также и меняется ux, uy, uz
Витоге мы имеем начальный базис ux, uy, uz, и новый базис
ux', uy', uz'. Вычисляем матрицу перехода от старого базиса к
новому, а после перемножаем все точки на матрицу перехода и получаем
новые координаты. Если есть альтернативные предложения, то your welcome*/
void RotateObject::apply(Object &obj, Options &opt)
{
    /*В качестве параметров идут dx,dy,dz для */
    Vector d_p = Vector(opt[0], opt[1], opt[2]);
    Vector n_dir = obj.dir + d_p;
    Vector n_ux = n_dir;

    Vector n_uy = Vector(0, 1, 0);
    Vector n_uz = n_uy * n_ux;
    n_uy = n_ux * n_uz;

    n_ux.normalize();
    n_uy.normalize();
    n_uz.normalize();

    double mtx[SIZE][SIZE] = {
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {0, 0, 0, 1}
    };

    double n_mtx[SIZE][SIZE] = {
        {obj.ux.x, obj.uy.x, obj.uz.x, 0},
        {obj.ux.y, obj.uy.y, obj.uz.y, 0},
        {obj.ux.z, obj.uy.z, obj.uz.z, 0},
        {0, 0, 0, 1}
    };

    Matrix inv = Matrix::inv(Matrix(mtx));
    Matrix n = Matrix(n_mtx);

    Matrix m_tr = Matrix::multiplicate(inv, n);

    for (Point point : obj.vertex_trans)
    {
        point = Matrix::multiplicate(point, m_tr);
    }

    obj.dir = n_dir;
    obj.ux = n_ux;
    obj.uy = n_uy;
    obj.uz = n_uz;
}


void RotateCamera::apply(Camera &cam, Options &opt)
{
    Point p = Point(opt.params[0], opt.params[1], opt.params[2], 1.);
    cam.target += p;

    // Для работы с плоскостями также надо производить изменение значений
}

void MoveCamera::apply(Camera &cam, Options &opt)
{
    Point p = Point(opt.params[0], opt.params[1], opt.params[2], 1.);
    cam.position += p;
    cam.target += p;

    // Для работы с плоскостями также надо производить изменение значений
}



Vector Transformation::apply(const Vector &vector,
    Action &act, Options &opt)
{
    return act.apply(vector, opt);
}

Point Transformation::apply(Point &point,
     Action &act, Options &opt)
{
    Point p;
    Vector vk;
    Vector v(point, p);
    Vector after = act.apply(v, opt);
    return after.asPoint();
}

void Transformation::apply(Camera &cam, Action &act, Options &opt)
{
    act.apply(cam, opt);
}

