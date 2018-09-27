#include "drawer.h"
#include <qDebug>
Drawer::Drawer(QGraphicsScene *graphics_scene)
{
    this->graphics_scene = graphics_scene;
}

void Drawer::draw_objects(const ObjectList &objs)
{
    int vindex_0, vindex_1, vindex_2;

    Point p0, p1, p2;

    for(Object obj : objs.objects)
    {
        for (Triangle pol:obj.polygons)
        {

            if (!(pol.state & POLYGON_STATE_ACTIVE) ||
                (pol.state & POLYGON_STATE_CLIPPED) ||
                (pol.state & POLYGON_STATE_BACKFACE))
                continue;

            vindex_0 = pol.indexes_vert[0];
            vindex_1 = pol.indexes_vert[1];
            vindex_2 = pol.indexes_vert[2];

            p0 = obj.vertex_trans[vindex_0];
            p1 = obj.vertex_trans[vindex_1];
            p2 = obj.vertex_trans[vindex_2];

            this->draw_line(p0.x, p0.y,
                            p1.x, p1.y,
                            pol.color);

            this->draw_line(p1.x, p1.y,
                            p2.x, p2.y,
                            pol.color);

            this->draw_line(p2.x, p2.y,
                            p0.x, p0.y,
                            pol.color);
        }
    }
}
void Drawer::draw_line(int x1, int y1,
                       int x2, int y2,
                       QColor color)
{
    this->graphics_scene->addLine(
                x1,  y1, x2, y2, QPen(Qt::black));



}
