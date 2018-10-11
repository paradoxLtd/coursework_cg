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



    qDebug() << "OBJ";
    for(Object obj : objs.objects)
    {

         int i = 0;

        for (Triangle pol:obj.polygons)
        {
            /*if (i > 1)
                break;*/

            if (!(pol.state & POLYGON_STATE_ACTIVE) ||
                (pol.state & POLYGON_STATE_CLIPPED) ||
                (pol.state & POLYGON_STATE_BACKFACE))
                continue;

            vindex_0 = pol.indexes_vert[0];
            vindex_1 = pol.indexes_vert[1];
            vindex_2 = pol.indexes_vert[2];

            qDebug() << vindex_0 << " " << vindex_1 << " " << vindex_2;

            p0 = obj.vertex_trans[vindex_0];
            p1 = obj.vertex_trans[vindex_1];
            p2 = obj.vertex_trans[vindex_2];

            p0.set_p_color(Vector(1.0, 0, 0));
            p1.set_p_color(Vector(0, 1.0, 0));
            p2.set_p_color(Vector(0, 0, 1.0));

            /*this->draw_line(p0.x, p0.y,
                            p1.x, p1.y,
                            Qt::black);

            this->draw_line(p1.x, p1.y,
                            p2.x, p2.y,
                            Qt::black);

            this->draw_line(p2.x, p2.y,
                            p0.x, p0.y,
                            Qt::black);*/
            this->triangle_rasterize(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, colors[i]);
            this->set_color(colors[i]);
            //this->RasterizeTriangle(p0, p1, p2);
            //this->color = colors[i];

            ++i;

            //qDebug() << p0.x << " " << p1.x << " " << p2.x << p0.y << " " << p1.y << " " << p2.y;
        }
    }

    update();
}

//затенение по Гуро 827
//освещение 840
//отсечение 914
//изменения в камере 928
//прототипы функций освещения 933
//текстуры с корректной перспективой 1069
//с.815
void Drawer::triangle_rasterize(int x1, int y1, int x2, int y2, int x3, int y3, QColor color)
{
    // Упорядочиваем точки p1(x1, y1),
      // p2(x2, y2), p3(x3, y3)
      if (y2 < y1) {
            std::swap(y1, y2);
            std::swap(x1, x2);
      } // точки p1, p2 упорядочены
      if (y3 < y1) {
            std::swap(y1, y3);
            std::swap(x1, x3);
      } // точки p1, p3 упорядочены
      // теперь p1 самая верхняя
      // осталось упорядочить p2 и p3
      if (y2 > y3) {
            std::swap(y2, y3);
            std::swap(x2, x3);
      }
      // приращения по оси x для трёх сторон
      // треугольника
      fixed dx13 = 0, dx12 = 0, dx23 = 0;
      // вычисляем приращения
      // в случае, если ординаты двух точек
      // совпадают, приращения
      // полагаются равными нулю
      if (y3 != y1) {
            dx13 = int_to_fixed(x3 - x1);
            dx13 /= y3 - y1;
      }
      else
      {
            dx13 = 0;
      }

      if (y2 != y1) {
            dx12 = int_to_fixed(x2 - x1);
            dx12 /= (y2 - y1);
      }
      else
      {
            dx12 = 0;
      }

      if (y3 != y2) {
            dx23 = int_to_fixed(x3 - x2);
            dx23 /= (y3 - y2);
      }
      else
      {
            dx23 = 0;
      }
      // "рабочие точки"
      // изначально они находятся в верхней  точке
      fixed wx1 = int_to_fixed(x1);
      fixed wx2 = wx1;
      // сохраняем приращение dx13 в другой переменной
      int _dx13 = dx13;

      // упорядочиваем приращения таким образом, чтобы
      // в процессе работы алгоритмы
      // точка wx1 была всегда левее wx2
      if (dx13 > dx12)
      {
            std::swap(dx13, dx12);
      }
      // растеризуем верхний полутреугольник
      for (int i = y1; i < y2; i++){
            // рисуем горизонтальную линию между рабочими
            // точками
            for (int j = fixed_to_int(wx1); j <= fixed_to_int(wx2); j++){
                setPixel(j, i, color);
            }
            wx1 += dx13;
            wx2 += dx12;
      }
      // вырожденный случай, когда верхнего полутреугольника нет
      // надо разнести рабочие точки по оси x, т.к. изначально они совпадают
      if (y1 == y2){
            wx1 = int_to_fixed(x1);
            wx2 = int_to_fixed(x2);
      }
      // упорядочиваем приращения
      // (используем сохраненное приращение)
      if (_dx13 < dx23)
      {
            std::swap(_dx13, dx23);
      }
      // растеризуем нижний полутреугольник
      for (int i = y2; i <= y3; i++){
            // рисуем горизонтальную линию между рабочими
            // точками
            for (int j = fixed_to_int(wx1); j <= fixed_to_int(wx2); j++){
                  setPixel(j, i, color);
            }
            wx1 += _dx13;
            wx2 += dx23;
      }

      //update();
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


    qDebug() << "TRps";
    qDebug() << "TRs " << this->color;
    qDebug() << maxYPoint.x <<" " << maxYPoint.y;
    qDebug() << middleYPoint.x <<" " << middleYPoint.y;
    qDebug() << minYPoint.x <<" " << minYPoint.y;

    ScanTriangle(minYPoint, middleYPoint, maxYPoint,
            Vector::vectorMultiplication(Vector(maxYPoint, minYPoint), Vector(middleYPoint, minYPoint)).z >= 0);
}

void Drawer::ScanTriangle(Vertex minYPoint, Vertex middleYPoint, Vertex maxYPoint, bool handedness)
{
    /*Формируем градиент - высчитываем значения приращений цвета
    при изменении шага по x и по y*/

    Gradient gr = Gradient(minYPoint, middleYPoint, maxYPoint);
    /*Edge topToBottom  = Edge(gr, minYPoint, maxYPoint, 0);
    Edge topToMiddle  =  Edge(gr, minYPoint, middleYPoint, 0);
    Edge middleToBottom =  Edge(gr, middleYPoint, maxYPoint, 1);*/

    Edge topToBottom  = Edge(gr, minYPoint, maxYPoint, 0);
    Edge topToMiddle  =  Edge(gr, middleYPoint, maxYPoint, 0);
    Edge middleToBottom =  Edge(gr, minYPoint, middleYPoint, 0);

    /*qDebug() << "Edges " << this->color;
    qDebug() << topToBottom.get_x() << " " << topToBottom.get_y_start() << " " << topToBottom.get_y_end();
    qDebug() << topToMiddle.get_x() << " " << topToMiddle.get_y_start() << " " << topToMiddle.get_y_end();
    qDebug() << middleToBottom.get_x() << " " << middleToBottom.get_y_start() << " " << middleToBottom.get_y_end();*/

    ScanEdges(gr, topToBottom, topToMiddle, handedness);
    ScanEdges(gr, topToBottom, middleToBottom, handedness);
}

void Drawer::ScanEdges(Gradient gr, Edge a, Edge b, bool handedness)
{
    Edge left = a;
    Edge right = b;
    if(handedness)
    {
        std::swap(left, right);
    }

    int y_start = b.get_y_start();
    int y_end  = b.get_y_end();


    qDebug() << "Y's " <<  y_start << " " << y_end;
    qDebug() << "X's before " << left.get_x() << right.get_x();

    for(int j = y_start; j < y_end; j++)
    {
        DrawScanLine(gr, left, right, j);
        left.step();
        right.step();
    }
    qDebug() << "X's after " << left.get_x() << right.get_x();

    /*qDebug() << topToBottom.get_x() << " " << topToBottom.get_y_start() << " " << topToBottom.get_y_end();
    qDebug() << topToMiddle.get_x() << " " << topToMiddle.get_y_start() << " " << topToMiddle.get_y_end();
    qDebug() << middleToBottom.get_x() << " " << middleToBottom.get_y_start() << " " << middleToBottom.get_y_end();*/
}

void Drawer::DrawScanLine(Gradient gr, Edge left, Edge right, int j)
{
    int x_min = std::ceil(left.get_x());
    int x_max = std::ceil(right.get_x());

    double x_prestep = x_min - left.get_x();

    Vector color = left.get_color() + gr.get_color_x_step() * x_prestep;

    for(int i = x_min; i < x_max; i++)
    {
        /*int r = color.x;// * 255.0f ;
        int g = color.y;// * 255.0f ;
        int b =  color.z;// * 255.0f ;*/

        //qDebug() << "COLOR VAL " << r << " " << g << " " << b;

        setPixel(i, j, this->color);
        //color = color + gr.get_color_x_step();
        //DrawPixel(i, j, (byte)0xFF, (byte)0xFF, (byte)0xFF, (byte)0xFF);
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
