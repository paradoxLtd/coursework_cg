#include "drawer.h"
#include <qDebug>

#include "fixed.h"
#include "float.h"
#include <QDir>

Drawer::Drawer(Bitmap *bitmap)
{
    this->bitmap = bitmap;
    this->color = Qt::black;
    m_zBuffer.resize(WIDTH_WIN * HEIGHT_WIN);
}
void Drawer::ClearDepthBuffer()
{
    for(int i = 0; i < m_zBuffer.size(); i++)
    {
        m_zBuffer[i] = FLT_MAX;

    }
}

void Drawer::draw_objects(const ObjectList &objs)
{
    int vindex_0, vindex_1, vindex_2;

    Point p0, p1, p2;

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

            /*p0.set_p_color(Vector(1.0, 0, 0));
            p1.set_p_color(Vector(0, 1.0, 0));
            p2.set_p_color(Vector(0, 0, 1.0));*/

            //this->triangle_rasterize(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, colors[i]);
            this->set_color(colors[i]);

            int h_tex = 25, w_tex = 25;
            QImage texture;
            bool err = texture.load(QDir::currentPath().append("/ice.jpg"));
            //texture = texture.scaled(w_tex, h_tex, Qt::KeepAspectRatio);
            //qDebug() << "FFFFFFFFF "<< texture.size().width() << " " << texture.size().height() << " " << err;

            Vertex p0_vertex(p0, Point(0.0f, 0.0f, 0.0f, 0.0f));
            Vertex p1_vertex(p1, Point(0.5f, 1.0f, 0.0f, 0.0f));
            Vertex p2_vertex(p2, Point(1.0f, 0.0f, 0.0f, 0.0f));
            this->RasterizeTriangle(p0_vertex, p1_vertex, p2_vertex, texture);

            ++i;
            //qDebug() << p0.x << " " << p1.x << " " << p2.x << p0.y << " " << p1.y << " " << p2.y;
        }
    }

    update();
}


//Хорошая статья про растеризацию, текстуры и т. д.
//https://habr.com/post/257107/
void Drawer::RasterizeTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint, QImage &texture)
{
    /*Производим сортировку переданных вершин треугольника
    по координате Y: maxYPoint.y >= middleYPoint.y >= minYPoint.y*/


    if(maxYPoint.GetY() < middleYPoint.GetY())
    {
       std::swap(maxYPoint, middleYPoint);
    }

    if(middleYPoint.GetY() < minYPoint.GetY())
    {
        std::swap(middleYPoint, minYPoint);
    }

    if(maxYPoint.GetY() < middleYPoint.GetY())
    {
       std::swap(maxYPoint, middleYPoint);
    }
    ScanTriangle(minYPoint, middleYPoint, maxYPoint,
            Vector::vectorMultiplication(Vector(maxYPoint.get_pos(), minYPoint.get_pos()), Vector(middleYPoint.get_pos(), minYPoint.get_pos())).z >= 0, texture);
}

void Drawer::ScanTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint, bool handedness, QImage &texture)
{

    /*Формируем градиент - высчитываем значения приращений цвета
    при изменении шага по x и по y*/

    Gradient gr = Gradient(minYPoint, middleYPoint, maxYPoint);

    Edge topToBottom  = Edge(gr, minYPoint, maxYPoint, 0);
    Edge topToMiddle  =  Edge(gr, minYPoint, middleYPoint, 0);
    Edge middleToBottom =  Edge(gr, middleYPoint, maxYPoint, 1);

    ScanEdges(gr, topToBottom, topToMiddle, handedness, texture);
    ScanEdges(gr, topToBottom, middleToBottom, handedness, texture);
}

void Drawer::ScanEdges(Gradient gr, Edge &a, Edge &b, bool handedness, QImage &texture)
{

    int y_start = b.get_y_start();
    int y_end  = b.get_y_end();

    //qDebug() << "SWWWWWWWWWWWW " <<  y_start<< " "<< y_end;
    Edge left = a;
    Edge right = b;

    if (handedness) {
        std::swap(left, right);
    }


    //qDebug() << "Y's " <<  y_start << " " << y_end;
    //qDebug() << "X's before " << left.get_x() << right.get_x();

    for(int j = y_start; j < y_end; j++)
    {

        DrawScanLine(gr, left, right, j, texture);
        a.step();
        b.step();
        left.step();
        right.step();

    }
}

void Drawer::DrawScanLine(Gradient gr, Edge left, Edge right, int j, QImage &texture)
{
    int x_min = std::ceil(left.get_x());
    int x_max = std::ceil(right.get_x());

    double x_prestep = x_min - left.get_x();
    float xDist = right.get_x() - left.get_x();

    float depthXStep = (right.getDepth() - left.getDepth())/xDist;
    float depth = left.getDepth() + depthXStep * x_prestep;

    float texCoordX = left.GetTexCoordX() + gr.GetTexCoordXXStep() * x_prestep;
    float texCoordY = left.GetTexCoordY() + gr.GetTexCoordYXStep() * x_prestep;
    //Vector color = left.get_color() + gr.get_color_x_step() * x_prestep;

    for(int i = x_min; i < x_max; i++)
    {
        int index = i + j * WIDTH_WIN;
        if (depth < this->m_zBuffer[index]) {
            m_zBuffer[index] = depth;
            //int r = color.x * 255.0f ;
            //int g = color.y * 255.0f ;
            //int b =  color.z * 255.0f ;
            //setPixel(i, j, QColor(r, g, b));
            int srcX = (int)(texCoordX * (texture.size().width() - 1) + 0.5f);

            //Point out that this was changed to get height in video 16
            int srcY = (int)(texCoordY * (texture.size().height() - 1) + 0.5f);

            //setPixel(i, j, Qt::red);

            copyPixel(i, j, srcX, srcY, texture);
            //qDebug() << texCoordX << " " << texCoordY;
            texCoordX += gr.GetTexCoordXXStep();
            texCoordY += gr.GetTexCoordYXStep();
        }

        //color += gr.get_color_x_step();
        depth += depthXStep;
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


void Drawer::copyPixel(int destX, int destY, int srcX, int srcY, QImage &texture)
{
    setPixel(destX, destY, QColor(texture.pixel(srcX, srcY)));
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
