#include "material.h"


Material::Material(int state, int id, std::string name, QColor color, double ka, double kd, double ks, std::string texture_name)
{
    this->state = state;
    this->id = id;
    this->name = name;
    this->color = color;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    /*this->ra = color * ka;
    this->rd = color * kd;
    this->rs = color * ks;*/
    this->texture_name = texture_name;
}

