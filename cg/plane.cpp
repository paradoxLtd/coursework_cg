#include "plane.h"

Plane::Plane(Point &point, Vector &n, bool normalize)
{
    this->p = point;
    this->n = n;
    this->normalize = normalize;

    if (normalize) {
        this->n.normalize();
    }
}

Plane::Plane(const Plane &p)
{
    this->p = p.p;
    this->n = p.n;
    this->normalize = p.normalize;
}

Plane::Plane(Plane &&p)
{
    this->p = p.p;
    this->n = p.n;
    this->normalize = p.normalize;

    //p.n = nullptr;
    p.p = nullptr;
    p.normalize = false;
}

Plane& Plane::operator=(const Plane &p)
{
    this->p = p.p;
    this->n = p.n;
    this->normalize = p.normalize;

    return *this;
}

Plane& Plane::operator=(Plane &&p)
{
    this->p = p.p;
    this->n = p.n;
    this->normalize = p.normalize;

    p.p = nullptr;
    //p.n = nullptr;
    p.normalize = false;

    return *this;
}

double Plane::compute_point_in_plane(Point p)
{
    return this->n.x * (p.x - this->p.x) + this->n.y * (p.y - this->p.y) + this->n.z * (p.z - this->p.z);
}
