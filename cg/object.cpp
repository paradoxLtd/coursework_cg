#include "Object.h"

void Object::saveVertixes()
{
    vertex_trans = vertex_local;
}

void Object::saveTextures()
{
    texture_coords = texture_coords_trans;
}

void Object::reset()
{
        // Сбросим флаг объекта, соответствующий отбраковке
        this->state = OBJECT_STATE_ACTIVE;

        // Теперь сделаем то же самое для флагов отсечения и
        // обратных поверхностей многоугольников
        for (Triangle pol : polygons)
        {
            // Если треугольник виден
            if (!(pol.state &  POLYGON_STATE_ACTIVE))
                continue;
            RESET_BIT(pol.state, POLYGON_STATE_CLIPPED);
            RESET_BIT(pol.state, POLYGON_STATE_BACKFACE);
        }
}

void Object::create(std::vector<Point> vertex_local,
             std::vector<Point> texture_coords,
             Vector ux, Vector uy, Vector uz,
             Vector dir, Point center, int attr,
            int state, const char *name)
{
    this->id = get_id();
    this->state = state;
    this->attr = attr;
    this->center = center;
    this->dir = Vector(1, 0, 0);
    this->ux =  Vector(1, 0, 0);
    this->uy =  Vector(0, 1, 0);
    this->uz =  Vector(0, 0, 1);
    this->vertex_local = vertex_local;
    this->vertex_trans = vertex_local;
    this->texture_coords = texture_coords;
    this->texture_coords_trans = texture_coords;
    this->polygons = polygons;
    this->name = name;

    // Получаем avg_radius и max_radius
    updateRad();
}

Object::Object(std::vector<Point> v1,
             std::vector<Point> v2,
             Vector ux, Vector uy, Vector uz,
             Vector dir, Point center, int attr,
            int state, const char *name)
 {
    create(v1, v2, ux, uy, uz, dir, center, attr, state, name);
 }

void Object::updateRad()
{
    if (vertex_local.size() < 3)
    {
        return;
    }

    double mx = max_radius * max_radius, curr = 0;
    double px, py, pz;
    avg_radius = 0;
    for (Point p : vertex_local)
    {
        px = p.x; py = p.y; pz = p.z;
        if ((curr = (px * px + py * py + pz * pz)) > mx)
            mx = curr;
        avg_radius += curr;
    }
    max_radius = sqrt(mx);
    avg_radius /= vertex_local.size();
}

void Object::update()
{
    reset();
    saveVertixes();
    saveTextures();
    updateRad();
}

int Object::next_id = 0;
