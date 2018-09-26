#include "drawer.h"
#include <qDebug>
Drawer::Drawer(QGraphicsScene *graphics_scene)
{
    this->graphics_scene = graphics_scene;
}

void Drawer::draw_objects(const ObjectList &objs)
{
    int vindex_0, vindex_1, vindex_2;
    int pSize;

    for(Object obj : objs.objects)
    {
        pSize = obj.polygons.size();
        for(int poly = 0; poly < pSize; poly++)
        {
            if (!(obj.polygons[poly].state & POLYGON_STATE_ACTIVE) ||
                (obj.polygons[poly].state & POLYGON_STATE_CLIPPED) ||
                (obj.polygons[poly].state & POLYGON_STATE_BACKFACE))
                continue;
            vindex_0 = obj.polygons[poly].indexes_vert[0];
            vindex_1 = obj.polygons[poly].indexes_vert[1];
            vindex_2 = obj.polygons[poly].indexes_vert[2];
            qDebug() << obj.vertex_trans[vindex_0].x << " " << obj.vertex_trans[vindex_0].y;
            this->draw_line(obj.vertex_trans[vindex_0].x,
                            obj.vertex_trans[vindex_0].y,
                            obj.vertex_trans[vindex_1].x,
                            obj.vertex_trans[vindex_1].y,
                            obj.polygons[poly].color);
            this->draw_line(obj.vertex_trans[vindex_1].x,
                            obj.vertex_trans[vindex_1].y,
                            obj.vertex_trans[vindex_2].x,
                            obj.vertex_trans[vindex_2].y,
                            obj.polygons[poly].color);
            this->draw_line(obj.vertex_trans[vindex_2].x,
                            obj.vertex_trans[vindex_2].y,
                            obj.vertex_trans[vindex_0].x,
                            obj.vertex_trans[vindex_0].y,
                            obj.polygons[poly].color);
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
