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

    void draw_line(int x1, int y1,
                   int x2, int y2,
                   QColor color = Qt::black);
};

#endif // DRAWER_H
