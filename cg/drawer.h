#ifndef DRAWER_H
#define DRAWER_H

#include "defines.h"

#include "objectlist.h"
#include <QGraphicsScene>

#include "bitmap.h"
#include "edge.h"
#include "vertex.h"
#include <cmath>
#include <algorithm>



class Drawer
{

public:
    Drawer() = default;
    Drawer(Bitmap *bitmap);

    void draw_objects(const ObjectList &objs);
    void clear();


    void RasterizeTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint);
    void ScanTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint, bool handedness);
    void ScanEdges(Gradient gr, Edge &a, Edge &b, bool handedness);
    void DrawScanLine(Gradient gr, Edge left, Edge right, int j);


    void set_color(QColor color);
    void ClearDepthBuffer();
    static QColor multuply_color(QColor color, double num);



private:
    Bitmap *bitmap;
    QPainter painter;
    QPen pen;
    std::vector <float> m_depth;
    QColor color;
    std::vector<float> m_zBuffer;

    void update();
    void draw_line(int x1, int y1,
                   int x2, int y2,
                   QColor color = Qt::black);
    void setPixel(int x, int y, QColor color);
};

#endif // DRAWER_H
