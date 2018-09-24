#include "Triangle.h"

void Triangle::init(Object* ob, Indexes v,
                    Indexes vt, /*Indexes &vn,*/
                    int s, int a, QColor c)
{
    this->object = ob;
    this->indexes_vert = v;
    this->indexes_text = vt;
    //this->indexes_norm = vn;
    // поскольку в загрузчике Triangle создается пустым без
    // точек, то посчитать нормаль все равно нельзя
    //this->normal = normalTrans();
    this->state = s;
    this->attr = a;
    this->color = c;

    this->indexes_vert.name = "Vertex indexes";
    this->indexes_text.name = "Texture indexes";
    this->normal.name = "Normal Vector";
}

Triangle::Triangle(Object* ob, Indexes v,
                   Indexes vt, /*Indexes &vn,*/
                   int s, int a, QColor c)
{
    init(ob, v, vt, s, a, c);
}

void Triangle::copy(const Triangle& t) noexcept
{
    init(t.object, t.indexes_vert,
         t.indexes_text, t.state,
         t.attr, t.color);
}

void Triangle::destroy() noexcept
{
    object = nullptr;
}

Triangle::Triangle(const Triangle &triangle)
{
    copy(triangle);
}

Triangle::~Triangle()
{
    destroy();
}

Triangle& Triangle::operator=(const Triangle& other) noexcept
{
    destroy();
    copy(other);
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other)noexcept
{
    destroy();
    copy(other);
    other.destroy();
    return *this;
}

// 581 Получить вектор нормали
Vector Triangle::getNormal(std::vector<Point> vertix)
const noexcept
{
    int vsize = vertix.size();
    if (vsize < 3)
    {
        std::cout << "\nPolygon consists " <<
        vertix.size() << " points, but need >2.";
        return Vector(POLYGON_HAVE_TOO_FEW_POINTS,
                      POLYGON_HAVE_TOO_FEW_POINTS,
                      POLYGON_HAVE_TOO_FEW_POINTS);
    }

    int isize = indexes_vert.size();
    if (isize < 3)
    {
        std::cout << "\nIndexes consist of " <<
        vertix.size() << " point, but need >2.";
        return Vector(INDEXES_HAVE_TOO_FEW_POINTS,
                      INDEXES_HAVE_TOO_FEW_POINTS,
                      INDEXES_HAVE_TOO_FEW_POINTS);
    }
    for (int i = 0; i < isize; i++)
    {
        if (indexes_vert[i] >= vsize)
        {
            std::cout << "\nOne of indexex is more then Size(" <<
            vertix.size() << "). Is it strange?";
            return Vector(INDEXES_INDEX_MORE_THEN_SIZE,
                          INDEXES_INDEX_MORE_THEN_SIZE,
                          INDEXES_INDEX_MORE_THEN_SIZE);
        }
    }

    // Векторы плоскости, которые векторно умножатся
    // и дадут вектор нормали.
    Vector u, v, n;

    // 3 точки полигона, задающие плоскости
    Point p0 = vertix[indexes_vert[0]];
    Point p1 = vertix[indexes_vert[1]];
    Point p2 = vertix[indexes_vert[2]];

    // Обход вершин осуществляется по часовой стрелке,
    // так что u=pO->p1, v=p0->p2, n=u*v

    u = Vector(p0, p1);
    v = Vector(p0, p2);
    n = Vector::vectorMultiplication(u, v);

    return n;
}

// нормаль для измененного полигона(после преобразо
// ваний из одних координат в другие)
Vector Triangle::normalTrans() const noexcept
{
    return getNormal(object->vertex_trans);
}

// Сравнение полигонов
bool Triangle::isEqual(
    const Triangle &O) noexcept
{
    return ((indexes_vert == O.indexes_vert)
            &&
            (indexes_text == O.indexes_text)
            &&
            (state == O.state) && (attr == O.attr)
            &&
            (object == O.object) && (color == O.color)
            &&
            (normal == O.normal)
            );
}

bool Triangle::operator==(const Triangle& other)noexcept
{
    return isEqual(other);
}

bool Triangle::operator!=(const Triangle& other)noexcept
{
    return !isEqual(other);
}

// Получить массив точек
std::vector<Point> Triangle::getPoints()
{
    std::vector<Point> for_return;
    std::vector<Point> take_from = object->vertex_local;
    for (int i = 0; i < indexes_vert.size(); i++)
    {
        for_return.push_back(take_from[i]);
    }
    return for_return;
}

std::ostream& operator<<(std::ostream& os,
                                const Triangle& tr)
{
    os << "\nPolygon(Objects id:" <<
          tr.object->id <<
          ", state: " << tr.state <<
          ", attr: " << tr.attr <<
          ")" << tr.indexes_vert <<
          tr.indexes_text <<
          tr.normal;
    return os;
}


