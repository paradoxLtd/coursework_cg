#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>
#include "../point.h"
#include "../vector.h"

//Эти дефайны вводятся для типа гибкости графического процессора
//По Факту будем использовать точечное освещение

#define LIGHT_ATTR_AMBIENT 0x0001
#define LIGHT_ATTR_INFINITE 0x0002
#define LIGHT_ATTR_POINT 0x0004
#define LIGHT_ATTR_SPOTLIGHT 0x0008

#define LIGHT_STATE_ON 1
#define LIGHT_STATE_OFF 0

#define MAX_LIGHTS 8


class Light
{
public:
    Light() = delete;
    Light(int state, int id, int attr, QColor ambient, QColor diffuse, QColor specular,
          Point pos, Vector dir, double kc, double kl, double kq);
    ~Light() = default;

    int state;
    int id;
    int attr;

    QColor ambient, diffuse, specular; //Интенсивности общего, диффузного и зеркального освещений

    Point pos; //Положение источника
    Vector dir; //Направление источника

    double kc, kl, kq; // Степени затухания: нулевой, первой и второй степени


};

#endif // LIGHT_H
