#include "Object.h"

void Object::reset()
{
        // Сбросим флаг объекта, соответствующий отбраковке
        RESET_BIT(this->state, OBJECT_STATE_CULLED);

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

Object::Object()
{
    id = get_id();
    state = OBJECT_STATE_NULL;
    attr = 0;
    avg_radius = 0;
    max_radius = 0;
    center = Point();
    dir = Vector(); ux = Vector(); uy = Vector(); uz = Vector();
    vertex_local = {};
    vertex_trans = {};
    vertices_size = 0;
    polygons = {};
    polygons_size = {};
    name = "no name";
}

void Object::updateRad()
{
    if (vertex_local.size() < 1)
        return;

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
int Object::next_id = 0;
