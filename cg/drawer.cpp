#include "drawer.h"
#include <qDebug>

#include "fixed.h"

Drawer::Drawer(Bitmap *bitmap)
{
    this->bitmap = bitmap;
    this->color = Qt::black;
}

void Drawer::draw_objects(const ObjectList &objs)
{
    int vindex_0, vindex_1, vindex_2;

    Vertex p0, p1, p2;

    QVector <QColor> colors = {Qt::black, Qt::blue, Qt::green, Qt::yellow,
                               Qt::red, Qt::darkBlue, Qt::magenta, Qt::cyan, Qt::darkGreen, Qt::darkRed, Qt::darkYellow, Qt::lightGray};

    //qDebug() << "OBJ";
    for(Object obj : objs.objects)
    {

         int i = 0;

        for (Triangle pol:obj.polygons)
        {
            /*if (i > 0)
                break;*/

            if (!(pol.state & POLYGON_STATE_ACTIVE) ||
                (pol.state & POLYGON_STATE_CLIPPED) ||
                (pol.state & POLYGON_STATE_BACKFACE))
                continue;

            vindex_0 = pol.indexes_vert[0];
            vindex_1 = pol.indexes_vert[1];
            vindex_2 = pol.indexes_vert[2];

            //qDebug() << vindex_0 << " " << vindex_1 << " " << vindex_2;

            p0 = obj.vertex_trans[vindex_0];
            p1 = obj.vertex_trans[vindex_1];
            p2 = obj.vertex_trans[vindex_2];

            p0.set_p_color(Vector(1.0, 0, 0));
            p1.set_p_color(Vector(0, 1.0, 0));
            p2.set_p_color(Vector(0, 0, 1.0));

            //this->triangle_rasterize(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, colors[i]);
            this->set_color(colors[i]);
            this->RasterizeTriangle(p0, p1, p2);

            ++i;
            //qDebug() << p0.x << " " << p1.x << " " << p2.x << p0.y << " " << p1.y << " " << p2.y;
        }
    }

    update();
}


//Хорошая статья про растеризацию, текстуры и т. д.
//https://habr.com/post/257107/
void Drawer::RasterizeTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint)
{
    /*Производим сортировку переданных вершин треугольника
    по координате Y: maxYPoint.y >= middleYPoint.y >= minYPoint.y*/

    if(maxYPoint.y < middleYPoint.y)
    {
       std::swap(maxYPoint, middleYPoint);
    }

    if(middleYPoint.y < minYPoint.y)
    {
        std::swap(middleYPoint, minYPoint);
    }

    if(maxYPoint.y < middleYPoint.y)
    {
       std::swap(maxYPoint, middleYPoint);
    }

    //qDebug() << "TRps";
    //qDebug() << "TRs " << this->color;
    //setPixel(maxYPoint.x, maxYPoint.y, Qt::green);
    //setPixel(middleYPoint.x, middleYPoint.y, Qt::green);
    //setPixel(minYPoint.x, minYPoint.y, Qt::green);
    //qDebug() << maxYPoint.x <<" " << maxYPoint.y;
    //qDebug() << middleYPoint.x <<" " << middleYPoint.y;
    //qDebug() << minYPoint.x <<" " << minYPoint.y;

    /*Vector minc = minYPoint.get_p_color();
    Vector midc = middleYPoint.get_p_color();
    Vector maxc = maxYPoint.get_p_color();
    assert(middleYPoint.x < maxYPoint.x);
    qDebug() << "VErtex colors";
    qDebug() << minc.x << minc.y << minc.z;
    qDebug() << midc.x << midc.y << midc.z;
    qDebug() << maxc.x << maxc.y << maxc.z;*/

    ScanTriangle(minYPoint, middleYPoint, maxYPoint,
            Vector::vectorMultiplication(Vector(maxYPoint, minYPoint), Vector(middleYPoint, minYPoint)).z >= 0);
}

void Drawer::ScanTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint, bool handedness)
{
    /*Формируем градиент - высчитываем значения приращений цвета
    при изменении шага по x и по y*/

    Gradient gr = Gradient(minYPoint, middleYPoint, maxYPoint);

    Edge topToBottom  = Edge(gr, minYPoint, maxYPoint, 0);
    Edge topToMiddle  =  Edge(gr, minYPoint, middleYPoint, 0);
    Edge middleToBottom =  Edge(gr, middleYPoint, maxYPoint, 1);

    ScanEdges(gr, topToBottom, topToMiddle, handedness);
    ScanEdges(gr, topToBottom, middleToBottom, handedness);
}

void Drawer::ScanEdges(Gradient gr, Edge &a, Edge &b, bool handedness)
{
    int y_start = b.get_y_start();
    int y_end  = b.get_y_end();

    Edge left = a;
    Edge right = b;

    if (handedness) {
        std::swap(left, right);
    }


    //qDebug() << "Y's " <<  y_start << " " << y_end;
    //qDebug() << "X's before " << left.get_x() << right.get_x();

    for(int j = y_start; j < y_end; j++)
    {
        DrawScanLine(gr, left, right, j);
        a.step();
        b.step();
        left.step();
        right.step();
    }
}

void Drawer::DrawScanLine(Gradient gr, Edge left, Edge right, int j)
{
    int x_min = std::ceil(left.get_x());
    int x_max = std::ceil(right.get_x());

    double x_prestep = x_min - left.get_x();

    Vector color = left.get_color() + gr.get_color_x_step() * x_prestep;

    for(int i = x_min; i < x_max; i++)
    {
        int r = color.x * 255.0f ;
        int g = color.y * 255.0f ;
        int b =  color.z * 255.0f ;

        setPixel(i, j, QColor(r, g, b));
        color = color + gr.get_color_x_step();
    }
}

void Drawer::set_color(QColor color)
{
    this->color = color;
}

QColor Drawer::multuply_color(QColor color, double num)
{
    color.setRgb(color.red() * num, color.green() * num, color.blue() * num);

    return color;
}





void Drawer::draw_line(int x1, int y1,
                       int x2, int y2,
                       QColor color)
{

    pen.setColor(color);
    painter.begin(&this->bitmap->get_image_ref());
    painter.setPen(pen);
    painter.drawLine(x1, y1, x2, y2);
    painter.end();
}

void Drawer::setPixel(int x, int y, QColor color)
{
    this->bitmap->get_image_ref().setPixelColor(x, y, color);
}

void Drawer::update()
{
    this->bitmap->update();
}

void Drawer::clear()
{
    this->bitmap->get_image_ref().fill(Qt::white);
}
