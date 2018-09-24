#ifndef DRAWER_H
#define DRAWER_H

#include "object.h"
#include <QGraphicsScene>

class Drawer
{

public:
    Drawer(QGraphicsScene* graphics_scene);

    void draw_object(Object &obj);
    void draw_line(int x1, int y1, int x2, int y2, QColor color);
private:
    QGraphicsScene* graphics_scene;
};

#endif // DRAWER_H
