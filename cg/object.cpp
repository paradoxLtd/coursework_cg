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

// Проецирование на плоскость
// https://stackoverflow.com/questions/9605556/how-to-project-a-point-onto-a-plane-in-3d/9605695#9605695
Point Object::project(Point p)
{
    Vector normal(uz);
    Vector v(center, p);
    double dist = Vector::scalarMultiplication(v, normal);
    double xx, yy, zz;
    xx = p.x - dist * normal.x;
    yy = p.y - dist * normal.y;
    zz = p.z - dist * normal.z;
    return Point(xx, yy, zz);
}

#include <map>
// http://rsdn.org/forum/cpp/1995781.all

// Отсортировать вершины по\против часовой
// https://stackoverflow.com/questions/6880899/sort-a-set-of-3-d-points-in-clockwise-counter-clockwise-order
void Object::sort()
{
    std::vector<std::pair<double, int>> angles;
    Point projected;
    int i = 0;
    for (Point p : vertex_local)
    {
        projected = project(p);
        angles push_back(atan2(projected.y, projected.x), i);
        i++;
    }

}

void Object::update()
{
    reset();
    saveVertixes();
    saveTextures();
    updateRad();
}

int Object::next_id = 0;
