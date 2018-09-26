#include "Transformation.h"
#include <cmath>

// Преобразования над векторами

// Движение
Vector Move::apply(const Vector &vector,
                   const Options &opt) const
{
    double x = opt[0], y = opt[1], z = opt[2];
    if (opt.inverse)
    {
        x *= -1; y *= -1; z *= -1;
    }

    Matrix move_matrix(
    {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 }
    });

    return Vector(
                Matrix::multiplicate(
                    vector, move_matrix));
}
// Масштабирование
Vector Scale::apply(const Vector &vector,
                    const Options &opt) const
{
    double x = opt[0], y = opt[1], z = opt[2];
    if (opt.inverse)
    {
        x = 1/x; y = 1/y; z = 1/z;
    }

    Matrix scale_matrix({
        { x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 }
    });
    return Vector(
                Matrix::multiplicate(
                    vector, scale_matrix));
}

/*
// Устаревшие повороты
Vector Rotate::rotateX(const Vector &vector,
                       double angle) const
{
    Matrix rotate_matrix({
        { 1,	0,				0,			0 },
        { 0,	cos(angle),		sin(angle), 0 },
        { 0,	-sin(angle),	cos(angle), 0 },
        { 0,	 0,				0,			1 }
    });
    return Vector(
                Matrix::multiplicate(
                    vector, rotate_matrix));
}

Vector Rotate::rotateY(const Vector &vector,
                       double angle) const
{
    double rotate_matrix[SIZE][SIZE] =
    {
        { cos(angle), 0,	 -sin(angle), 0 },
        { 0,		  1,	 0,			  0 },
        { sin(angle), 0,	 cos(angle),  0 },
        { 0,		  0,	 0,			  1 }
    };
    return Vector(
                Matrix::multiplicate(
                    vector, rotate_matrix));
}

Vector Rotate::rotateZ(const Vector &vector,
                       double angle) const
{
    double rotate_matrix[SIZE][SIZE] =
    {
        {  cos(angle), sin(angle), 0, 0 },
        { -sin(angle), cos(angle), 0, 0 },
        { 0,		   0,		   1, 0 },
        { 0,		   0,		   0, 1 }
    };
    return Vector(
                Matrix::multiplicate(
                    vector, rotate_matrix));
}

Vector Rotate::apply(const Vector &vector,
                     const Options &opt) const{
    int choose = static_cast<int>(opt[0]);
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
*/

// Преобразования над объектами

/*Как на мой взгляд стоит производить преобразования
К перемещениям стоит добавить также перенос center, а также
векторов dir, ux, uy, и uz
В случае поворотов мы получаем приращение для нашего вектора
dir, соответственно под него также и меняется ux, uy, uz
Витоге мы имеем начальный базис ux, uy, uz, и новый базис
ux', uy', uz'. Вычисляем матрицу перехода от старого базиса к
новому, а после перемножаем все точки на матрицу перехода и получаем
новые координаты. Если есть альтернативные предложения, то your welcome*/

Vector Rotate::apply( const Vector &v,
                    const Options &opt)const
{
    // не вызывать
    return v;
}

// Новый поворот объекта
void Rotate::apply(Object &obj,
                   const Options &opt) const
{
    if (fabs(opt[0] + opt[1] + opt[2]) < 0.001)
        return;
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

    Matrix mtx({
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {n_ux.x, n_uy.x, n_uz.x, 0},
        {0, 0, 0, 1}
    });

    Matrix n_mtx({
        {obj.ux.x, obj.uy.x, obj.uz.x, 0},
        {obj.ux.y, obj.uy.y, obj.uz.y, 0},
        {obj.ux.z, obj.uy.z, obj.uz.z, 0},
        {0, 0, 0, 1}
    });

    Matrix inv = Matrix::inv(mtx);

    Matrix m_tr = Matrix::multiplicate(inv, n_mtx);

    for (Point &point : obj.vertex_trans)
    {
        point = Matrix::multiplicate(point, m_tr);
    }

    obj.dir = n_dir;
    obj.ux = n_ux;
    obj.uy = n_uy;
    obj.uz = n_uz;
}

// Движение объекта
void Move::apply(Object &obj,
                 const Options &opt) const
{
    for (Point &point : obj.vertex_trans)
    {
        point = Transformation::transform(point, *this, opt);
    }
}

// Масштабирование объекта
void Scale::apply(Object &obj,
                  const Options &opt) const
{
    for (Point &point : obj.vertex_trans)
    {
        point = Transformation::transform(point, *this, opt);
    }
}


// Преобразования камеры

// Поворот
void Rotate::apply(Camera &cam,
                   const Options &opt) const
{
    Point p = Point(opt[0], opt[1], opt[2], 1.);
    cam.target += p;
    // Для работы с плоскостями также надо производить изменение значений
}

// Движение
void Move::apply(
        Camera &cam, const Options &opt) const
{
    Point p = Point(opt[0], opt[1], opt[2], 1.);
    cam.position += p;
    cam.target += p;

    // Для работы с плоскостями также надо производить изменение значений
}

// Масштабирование не задано!
void Scale::apply(Camera &cam,
                       const Options &opt) const
{

    // Для работы с плоскостями также надо производить изменение значений
}


// Применение трансформации
// к вектору
Vector Transformation::transform(
        const Vector &vector,
        const Action &act,
        const Options &opt)
{
    return act.apply(vector, opt);
}

// к точке
Point Transformation::transform(
        const Point &point,
        const Action &act,
        const Options &opt)
{
    Point p;
    Vector vk;
    Vector v(point, p);
    Vector after = act.apply(v, opt);
    return after.asPoint();
}

// к камере
void Transformation::transform(Camera &cam,
                               const Action &act,
                               const Options &opt)
{
    act.apply(cam, opt);
}

// к объекту
void Transformation::transform(Object &obj,
                               const Action &act,
                               const Options &opt)
{
    act.apply(obj, opt);
}

// Применение полных преобразований

// к объекту
void Transformation::fullTransform(Object &object,
                                   const MoveOptions &mop,
                                   const RotateOptions &rop,
                                   const ScaleOptions &sop)
{
    Move move;
    Rotate rotate;
    Scale scale;

    transform(object, move, mop);
    std::cout << "i moved here" << object;
    transform(object, scale, sop);
    std::cout << "i scaled here" << object;
    transform(object, rotate, rop);
    std::cout << "i rotated here" << rop[0] <<", " <<
                 rop[1] << ", " << rop[2]
              << object;
}

// к камере
void Transformation::fullTransform(Camera &camera,
                                   const MoveOptions &mop,
                                   const RotateOptions &rop,
                                   const ScaleOptions &sop)
{
    Move move;
    Rotate rotate;
    Scale scale;

    transform(camera, move, mop);
    transform(camera, rotate, rop);
    transform(camera, scale, sop);
}
