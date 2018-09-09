#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

//class Camera;
#include "point.h"
#include "vector.h"
#include "options.h"
#include "camera.h"
#include "object.h"
#include "matrix.h"
#include <iostream>



class Action
{
public:
    virtual Vector apply(const Vector &v, Options &opt) = 0;
    virtual void apply(Camera &cam, Options &opt) = 0;
    virtual void apply(Object &obj, Options &opt) = 0;
    virtual ~Action() = 0;
};

/*class ActionContainers
{
public:
    virtual void apply(Camera &cam, Options &opt) = 0;
    virtual void apply(Object &obj, Options &opt) = 0;
};*/


/*Как на мой взгляд стоит производить преобразования
К перемещениям стоит добавить также перенос center, а также
векторов dir, ux, uy, и uz

В случае поворотов мы получаем приращение для нашего вектора
dir, соответственно под него также и меняется ux, uy, uz
Витоге мы имеем начальный базис ux, uy, uz, и новый базис
ux', uy', uz'. Вычисляем матрицу перехода от старого базиса к
новому, а после перемножаем все точки на матрицу перехода и получаем
новые координаты. Если есть альтернативные предложения, то your welcome*/
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



class RotateObject : public Action
{
public:
    void apply(Object &obj, Options &opt) override;
};

class MoveObject : public Action
{
public:
    void apply(Camera &cam, Options &opt) override;
};

class ScaleObject : public Action
{

};

class RotateCamera : public Action
{
public:
    void apply(Camera &cam, Options &opt) override;
};

class MoveCamera : public Action
{
public:
    void apply(Camera &cam, Options &opt) override;
};

class ScaleCamera : public Action
{
//Ну это мы пока оставим
};


class Transformation
{
public:
    static Vector apply(const Vector &vector,
        Action &act, Options &opt);
    static Point apply(Point &point,
        Action &act, Options &opt);
    static void apply(Camera &cam, Action &act, Options &opt);
    static void apply(Object &obj, Action &act, Options &opt);
};


#endif // TRANSFORMATION_H
