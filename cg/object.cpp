#include "Object.h"

void Object::saveVertixes()
{
    vertex_trans = vertex_local;
}

void Object::saveTextures()
{
    texture_coords_trans = texture_coords;
}

void Object::pushPolygon(Triangle &tr)
{
    this->polygons.push_back(tr);
}

void Object::clearPolygons()
{
    this->polygons.clear();
}

void Object::reset()
{
        // Сбросим флаг объекта, соответствующий отбраковке
        this->state = OBJECT_STATE_ACTIVE;

        // Теперь сделаем то же самое для флагов отсечения и
        // обратных поверхностей многоугольников
        for (Triangle pol : polygons)
        {
            // Если треугольник виден
            if (!(pol.state &  POLYGON_STATE_ACTIVE))
                continue;
            RESET_BIT(pol.state, POLYGON_STATE_CLIPPED);
            RESET_BIT(pol.state, POLYGON_STATE_BACKFACE);
        }
}

void Object::create(std::vector<Point> vertex_local,
             std::vector<Point> texture_coords,
             Vector ux, Vector uy, Vector uz,
             Vector dir, Point center, int attr,
            int state, const char *name)
{
    this->id = get_id();
    this->state = state;
    this->attr = attr;
    this->center = center;
    this->dir = dir;
    this->ux =  ux;
    this->uy =  uy;
    this->uz =  uz;
    this->vertex_local = vertex_local;
    this->vertex_trans = vertex_local;
    this->texture_coords = texture_coords;
    this->texture_coords_trans = texture_coords;
    this->polygons = polygons;

    this->name = name;
    this->center.name = "Center point of Object";
    this->dir.name = "Direction vector";
    this->ux.name = "Vector ux";
    this->uz.name = "Vector uy";
    this->uy.name = "Vector uz";

    // Получаем avg_radius и max_radius
    updateRad();
}

Object::Object(std::vector<Point> v1,
             std::vector<Point> v2,
             Vector ux, Vector uy, Vector uz,
             Vector dir, Point center, int attr,
            int state, const char *name)
 {
    create(v1, v2, ux, uy, uz, dir, center, attr, state, name);
 }

void Object::updateRad()
{
    if (vertex_local.size() < 3)
    {
        return;
    }

    double mx = 0, curr = 0;
    double px, py, pz;
    avg_radius = 0;
    for (Point p : vertex_local)
    {
        px = p.x; py = p.y; pz = p.z;
        if ((curr = (px * px + py * py + pz * pz)) > mx)
            mx = curr;
        avg_radius += curr;
    }
    max_radius = sqrt(mx);
    avg_radius /= vertex_local.size();
}


//локальные функции к алгоритму Джарвиса
double vect(Point a1, Point a2, Point b1, Point b2); //косое произведение векторов a1a2 и b1b2
double dist2(Point a1, Point a2); // квадрат длины вектора a1a2
int first_point (std::vector<Point> set);//находит первую точку оболочки
//локальные функции к алгоритму ,,,


// https://stackoverflow.com/questions/18416861/how-to-find-convex-hull-in-a-3-dimensional-space/18418182#18418182

std::vector<int> Object::jarvis()
{
    std::vector<Point> set = vertex_local;

    int N = set.size();
    int i, t = 0, min;
    std::vector<Point> c_h; //b
    std::vector<int> indexes;

    //найдем первую точку оболочки
    i = first_point(set);
    c_h.push_back(set[i]);
    indexes.push_back(i);
    min=1;

    do         //ищем очередную точку оболочки
     {
         for(i = 1; i < N; i++)
         {
             if(
                     (vect(c_h[t], set[min], c_h[t], set[i]) < 0)
                     ||
                     (
                         (vect(c_h[t], set[min], c_h[t], set[i]) == 0)
                         &&
                         (dist2(c_h[t], set[min]) < dist2(c_h[t], set[i]))
                     )
               )
                 {
                   t++;
                   min = i;
                   c_h.push_back(set[min]);
                   indexes.push_back(i);
                   min = 0;
                 }
         }
     } while((c_h[t].x != c_h[0].x) && (c_h[t].y != c_h[0].y));

    return indexes;
}

double vect(Point a1, Point a2, Point b1, Point b2)
{
   double v;
   v=(a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
   return v;
}

double dist2(Point a1, Point a2) // квадрат длины вектора a1a2
{
   double v;
   v=(a2.x-a1.x)*(a2.x-a1.x)+(a2.y-a1.y)*(a2.y-a1.y);
   return v;
}

// Нахождение первой точки
int first_point (std::vector<Point> set)
{
   int N = set.size();
   int m = 0;
   for (int i = 1; i < N; i++)
     {
        if(
                (set[i].y < set[m].y)
                ||
                (
                    (set[i].y == set[m].y)
                    &&
                    (set[i].x > set[m].x)
                )
          )
        {
            m=i;
        }
     }
   return m;
}

// Алгоритм «заворачивания подарка» java



/*

// Проецирование на плоскость
// https://stackoverflow.com/questions/9605556/how-to-project-a-point-onto-a-plane-in-3d/9605695#9605695
Point Object::project(Point p)
{
    Vector normal(uz);
    Vector v(center, p);
    double dist = Vector::scalarMultiplication(v, normal);
    double xx, yy, zz;
    xx = p.x - dist * normal.x;
    yy = p.y - dist * normal.y;
    zz = p.z - dist * normal.z;
    return Point(xx, yy, zz);
}

double onThePlane(Triangle tr, Point p)
{
    std::vector<Point> v = tr.getPoints();
    if (v.size() < 3)
    {
        std::cout<< "\n points.size() < 3";
        return -1;
    }
    double V = (p.x - v[0].x)
            *
            (
                    (v[1].y - v[0].y)
                    *
                    (v[2].z - v[0].z)
                -
                    (v[1].z - v[0].z)
                    *
                    (v[2].y - v[0].y)
            )
            -
            (p.y-v[0].y)
            *
            (
                    (v[1].x - v[0].x)
                    *
                    (v[2].z - v[0].z)
                -
                    (v[1].z - v[0].z)
                    *
                    (v[2].x - v[0].x))+(p.z-a0.z)*
            ((a1.x-a0.x)*(a2.y-a0.y)-(a1.y-a0.y)*(a2.x-a0.x))
            )
}

void dun(Object obj)
{

}

// Знаковая площадь http://www.e-maxx-ru.1gb.ru/algo/oriented_area
double area_triangle(Point p1, Point p2, Point p3)
{
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x))/2;
}

// гуглится вот так https://yandex.ru/search/?text=алгоритм%20джарвиса%203l%20c%2B%2B&lr=213&clid=2270455&win=347

//http://studassistent.ru/c/algoritm-dzharvisa-c-si


// http://www.inf.tsu.ru/library/DiplomaWorks/CompScience/2004/Chadnov/diplom.pdf
//http://hardfire.ru/jarvis
void hull_jarvis(std::vector<Point>p, std::vector < int > &ip)
{
    int n = p.size();
    int first, q, next, i;
    double sign;
    // находим самую нижнюю из самых левых точек
    first = 0;
    for (i = 1; i < n; ++ i)
        if (p[i].x < p[first].x || (p[i].x == p[first].x && p[i].y < p[first].y))
            first = i;

    q = first; // текущая точка
    // добавляем точки в оболочку
    do
    {
        ip.push_back(q);
        next = q;
        // ищем следующую точку
        for (i = n - 1; i >= 0; -- i)
            if (p[i].x != p[q].x || p[i].y != p[q].y)
            {
                sign = area_triangle (p[q], p[i], p[next]);

                if (next == q || sign > 0 || (sign == 0 && point_in_box (p[next], p[q], p[i])))
                    next = i;
            }
        q = next;
    }
    while (q != first);
}

#include <map>
// http://rsdn.org/forum/cpp/1995781.all

// Отсортировать вершины по\против часовой
// https://stackoverflow.com/questions/6880899/sort-a-set-of-3-d-points-in-clockwise-counter-clockwise-order
void Object::sort()
{
    std::vector<std::pair<double, int>> angles;
    Point projected;
    int i = 0;
    for (Point p : vertex_local)
    {
        projected = project(p);
        //angles push_back(atan2(projected.y, projected.x), i);
        i++;
    }
}
// http://studassistent.ru/pascal-abc-net/zadano-mnozhestvo-tochek-v-trehmernom-prostranstve-nayti-vypukluyu-obolochku-naimenshego-obema-pascalabc-net
// https://stackoverflow.com/questions/20722933/how-can-i-construct-a-list-of-faces-from-a-list-of-edges-with-consistent-vertex/20723498#20723498
// https://ru.wikipedia.org/wiki/Полигональная_сетка#Элементы_моделирования_сетки
// http://www.inf.tsu.ru/library/DiplomaWorks/CompScience/2004/Chadnov/diplom.pdf
*/

/*
int levinshtein_damerau_matrix(QString s1, QString s2)
{
    //std::cout << "Matrix(Damerau-Levinshtein): \n";

    int len_s1 = s1.length();
    int len_s2 = s2.length();
    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;
    int str_matrix1 = (int )malloc((len_s2 + 1)*sizeof(int));
    int str_matrix2 = (int )malloc((len_s2 + 1)*sizeof(int));
    int str_matrix3 = (int )malloc((len_s2 + 1)*sizeof(int));


    for (int i = 0; i < len_s2 + 1; i++)
    {
        str_matrix1[i] = i;
    }
    str_matrix2[0] = 1;
    for (int i = 1; i < len_s2 + 1; i++)
    {
        str_matrix2[i] = levinshtein_fill_number(str_matrix2[i - 1], str_matrix1[i - 1], str_matrix1[i], s1[0] == s2[i - 1]);
    }

    for (int i = 2; i < len_s1 + 1; i++)
    {
        str_matrix3[0] = i;
        str_matrix3[1] = levinshtein_fill_number(str_matrix3[0], str_matrix2[0], str_matrix2[1], s1[i-1] == s2[0]);
        for (int j = 2; j < len_s2 + 1; j++)
        {
            str_matrix3[j] = levinshtein_damerau_fill_number(str_matrix3[j - 1], str_matrix2[j - 1], str_matrix2[j],
                    str_matrix1[j-2], s2[j - 1] == s1[i - 1],possible_transpos(s1[i - 2], s1[i - 1], s2[j - 2], s2[j - 1]));
        }
*/
        /*for (int i = 0; i < len_s2 + 1; i++)
        {
            std::cout << str_matrix1[i] << " ";
        }
        std::cout << "\n";*/
/*
        swap_int_poiter(&str_matrix1, &str_matrix2);
        swap_int_poiter(&str_matrix2, &str_matrix3);
    }
      */
    /*for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix1[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix2[i] << " ";
    }
    std::cout << "\n";*/
        /*
    int res = str_matrix2[len_s2];
    free(str_matrix1);
    free(str_matrix2);
    free(str_matrix3);
    return res;
}
*/

std::ostream& operator<<(std::ostream& os,
                                const Object& obj)
{
    os << "\n Object: object's id:" << obj.id <<
          "\n name: " << obj.name;
    os << "\n states:";
    if (obj.state & OBJECT_STATE_NULL)
          os << " not initialize;";
    if (obj.state & OBJECT_STATE_ACTIVE)
          os << " ready to render;";
    if (obj.state & OBJECT_STATE_VISIBLE)
          os << " visible;";
    if (obj.state & OBJECT_STATE_CULLED)
          os << " invisible;";
    if (obj.state & OBJECT_STATE_ERROR)
          os << " error;";

    os << "\n average radius: " <<
          obj.avg_radius;

    os << "\n maximum radius: " <<
          obj.max_radius;
    os << obj.center << obj.dir;

    if (obj.state & OBJECT_DETAILED)
    {
          os << "\n detailed information;";

         os << "\n physical attributes:";
         if (obj.attr & OBJECT_SINGLE_FRAME)
               os << " single frame;";
         if (obj.attr & OBJECT_MULTIPLE_FRAME)
               os << " multiple frame;";
         if (obj.attr & OBJECT_TEXTURE)
               os << " with textures;";

         os << obj.ux << obj.uy << obj.uz;

         os << "\n local vertex(" <<
               obj.vertex_local.size() << ")";
         for (Point point : obj.vertex_local)
         {
             os << point;
         }

         os << "\n local texture coords(" <<
               obj.texture_coords.size() << ")";
         for (Point point : obj.texture_coords)
         {
             os << point;
         }

         os << "\n trans texture coords(" <<
               obj.texture_coords_trans.size() << ")";
         for (Point point : obj.texture_coords_trans)
         {
             os << point;
         }

         os << "\n polygons(" <<
               obj.polygons.size() << ")";
         for (Triangle triangle : obj.polygons)
         {
             os << triangle;
         }
    }

    os << "\n trans vertex(" <<
          obj.vertex_trans.size() << ")";
    for (Point point : obj.vertex_trans)
    {
        os << point;
    }
}

void Object::update()
{
    reset();
    saveVertixes();
    saveTextures();
    updateRad();
}

int Object::next_id = 0;
