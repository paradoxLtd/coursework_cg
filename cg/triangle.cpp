#include "Triangle.h"

Triangle::Triangle(Object* ob, Indexes v, Indexes vt,
                   /*Indexes &vn,*/ int s, int a, QColor c)
{
    this->object = ob;
    this->indexes_vert = v;
    this->indexes_text = vt;
    //this->indexes_norm = vn;
    this->normal = normalTrans();
    this->state = s;
    this->attr = a;
    this->color = c;
}

void Triangle::copy(const Triangle& triangle) noexcept
{
    this->object = triangle.object;
    this->indexes_vert = triangle.indexes_vert;
    this->indexes_text = triangle.indexes_text;
    //this->indexes_norm = triangle.indexes_norm;
    this->normal = normalTrans();
    this->state = triangle.state;
    this->attr = triangle.attr;
    this->color = triangle.color;
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

std::ostream& operator<<(std::ostream& os,
                                const Triangle& tr)
{
    os << "\n Polygon: object's id:" << tr.object->id <<
          "\n Vertrix indexes" << tr.indexes_vert <<
          "\n Texture indexes" << tr.indexes_text <<
          "\n Vector normal" << tr.normal <<
          "\n state: " << tr.state << ", attr: " << tr.attr;
}


