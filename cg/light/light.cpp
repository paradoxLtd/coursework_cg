#include "light.h"

Light::Light(int state, int id, int attr, QColor ambient, QColor diffuse, QColor specular, Point pos, Vector dir, double kc, double kl, double kq)
{
    this->state = state;
    this->id = id;
    this->attr = attr;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->pos = pos;
    this->dir.normalize();
    this->kc = kc;
    this->kl = kl;
    this->kq = kq;
}
