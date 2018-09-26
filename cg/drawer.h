#ifndef DRAWER_H
#define DRAWER_H

#include "objectlist.h"
#include <QGraphicsScene>

class Drawer
{

public:
    Drawer(QGraphicsScene* graphics_scene = nullptr);

    void draw_objects(const ObjectList &objs);
private:
    QGraphicsScene* graphics_scene;

    void draw_line(double x1, double y1,
                   double x2, double y2,
                   QColor color = Qt::black);
};

#endif // DRAWER_H
