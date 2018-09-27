#include "objectlist.h"

void ObjectList::copy(const ObjectList &list)
{
    objects = list.objects;
}

ObjectList::ObjectList(const ObjectList &list)
{
    copy(list);
}

ObjectList::ObjectList(ObjectList &&list)
{
    objects = list.objects;
}

ObjectList& ObjectList::operator=
    (const ObjectList& list)
{
    copy(list);
    return *this;
};

ObjectList& ObjectList::operator=
    (ObjectList&& list)
{
    copy(list);
    return *this;
}

// Вместо objectlist.objects.push_back(...)
// теперь objectlist.push(...)
void ObjectList::push(Object &obj)
{
   objects.push_back(obj);
}

void ObjectList::clear()
{
   objects.clear();
}

int ObjectList::size() const
{
   return objects.size();
}

// Заведомо сюда не включены преобразования для
// точек текстур, ТОЛЬКО ДЛЯ ВЕРШИН
void ObjectList::prepareForConveyor
    (const MoveOptions &mop,
     const ScaleOptions &sop,
     const RotateOptions &rop)
{
    for (Object &obj : objects)
    {
        // обновление радиусов, сброс статусов(отсечен)
        // копирование исходных массивов в основные
        obj.update();
        Transformation::fullTransform(obj, mop, rop, sop);
    }
}

// Преобразование локальных координат
// к мировым
void ObjectList::localToWorld()
{
    Point point_tmp;
    Point center;
    for (Object &obj : objects)
    {
        center = obj.center;
        for (Point &point : obj.vertex_trans)
        {
            point += center;
        }
    }
}

void ObjectList::worldToCam(Camera &cam)
{
    cam.build_cam_matrix();

   for (Object &obj : objects)
   {
       for (Point &point : obj.vertex_trans)
       {
           std::cout << "\nbefore" << point;
           point = Matrix::multiplicate(
                       point, cam.mcam);
            std::cout << "\nafter" << point;
       }

       for (Point &point : obj.texture_coords_trans)
       {
           point = Matrix::multiplicate(point, cam.mcam);
       }

       obj.center = Matrix::multiplicate(obj.center, cam.mcam);
       obj.dir = Matrix::multiplicate(obj.dir, cam.mcam);
       obj.ux = Matrix::multiplicate(obj.ux, cam.mcam);
       obj.uy = Matrix::multiplicate(obj.uy, cam.mcam);
       obj.uz = Matrix::multiplicate(obj.uz, cam.mcam);
   }
   std::cout << *this;
}

// Проверка необходимости отсечения по плоскости Z
bool ObjectList::cutZ(int culL_flags,
                      const Point &sphere,
                      Object &obj,
                      const Camera &camera)
{
    // Координаты плоскостей отсечения камеры
    double farZ = camera.far_plane;
    double nearZ = camera.near_plane;

    // Радиус сферы и z-координата центра сферы
    double rad = obj.max_radius;
    double sZ = sphere.z;

    if (culL_flags & CULL_OBJECT_Z)
    {
        if ( // ближняя часть сферы за дальней плоскостью
                ((sZ - rad) > farZ)
                ||
                ((sZ + rad) < nearZ)
           ) // дальняя часть сферы перед ближней плоскостью
        {
            SET_BIT(obj.state, OBJECT_STATE_CULLED);
            return true;
        }
    }
    return false;
}

// Отбраковываем только по оси х
// Можно было бы воспользоваться уравнением
// плоскостей, но легче применить свойства подобных
// треугольников, так как это двумерная задача. Если
// область видимости имеет форму прямоугольного
// параллелепипеда, задача становится тривиальной,
// однако предположим, что это не так
bool ObjectList::cutX(int culL_flags, const Point &sphere,
                      Object &obj, const Camera &camera){
    // Радиус сферы
    double rad = obj.max_radius;

    // Ширина обзора камеры и дистанция до плоскости
    double width = camera.viewplane_width;
    double dist = camera.dst;

    // Координаты центра сферы
    double sX = sphere.x;
    double sZ = sphere.z;

    if (culL_flags & CULL_OBJECT_X)
    {
        // Выясняем положение самой правой и самой левой
        // точек ограничивающей сферы объекта относительно
        // правой и левой плоскостей отсечения
        double z_test = (0.5) * width * sZ / dist;

        if ( // левый конец сферы за правой стенкой обзора
                ((sX - rad) > z_test)
                ||
                ((sX + rad) < -z_test)
           ) // правый конец сферы за левой стенкой обзора
        {
            SET_BIT(obj.state, OBJECT_STATE_CULLED);
            return true;
        }
    }
    return false;
}

// По аналогии с X
bool ObjectList::cutY(int culL_flags, const Point &sphere,
                      Object &obj, const Camera &camera)
{
    // Радиус сферы
    double rad = obj.max_radius;

    // Высота обзора камеры и дистанция до плоскости
    double height = camera.viewplane_height;
    double dist = camera.dst;

    // Координаты центра сферы
    double sY = sphere.y;
    double sZ = sphere.z;

    if (culL_flags & CULL_OBJECT_Y)
    {
        // Выясняем положение самой верхней и самой нижней
        // точек ограничивающей сферы объекта относительно
        // правой и левой плоскостей отсечения
        double z_test = (0.5) * height * sZ / dist;

        if ( // Нижний конец сферы выше верхней плоскости
                ((sY - rad) > z_test)
                ||
                ((sY + rad) < -z_test)
           ) // Верхний конец сферы ниже нижней плоскости
        {
            SET_BIT(obj.state, OBJECT_STATE_CULLED);
            return true;
        }
    }
    return false;
}

// Отбраковка объектов, 574
// Данная функция отбраковывает объекты,
// не входящие в область видимости. При этом
// используются параметры камеры и объекта. С помощью
// параметра culL_flags определяется, по каким осям
// следует производить отсечение- по оси х,у,z или по
// всем, для чего все флаги нужно объединить с помощью
// побитового оператора ИЛИ. (Установлены дефайны)
// Если объект отбраковывается, его состояние изменяется.
// В функции предполагается, что и камера, и объект заданы
// корректно!

// Вызывать после всех преобразований

void ObjectList::removeObject(int culL_flags,
                              const Camera &camera)
{
    // Центр объекта в координатах камеры
    Point sphere_center;

    // Проход по всем объектам
    for (Object &obj : objects)
    {
        // Отбраковываем по оси z
        if (cutZ(culL_flags, sphere_center, obj, camera))
            continue;

        // Отбраковываем по оси x
        if (cutX(culL_flags, sphere_center, obj, camera))
            continue;

        // Отбраковываем по оси y
        if (cutY(culL_flags, sphere_center, obj, camera))
            continue;
    }
}

// 580
// ПРИМЕЧАНИЕ. В этой функции не используются матрицы,
// Функция удаляет из каркаса объекта все
// многоугольники, являющиеся обратными поверхностями,
// используя при этом параметры вершин, содержащиеся в
// списке vertex_trans, а также координаты точки, в
// которой расположена камера. Обратите внимание, что
// для каждого многоугольника устанавливается только
//состояниеобратной поверхности

void ObjectList::removeBackSurfaces(const Camera &camera)
{
    // Первая точка
    Point p0;

    // Вектор нормали и вектор, направленный в точку наблюдения
    Vector n, view;

    // Хранит результат скалярного произведения
    double dp;

    // Обрабатываем каждый объект сцены
    for (Object &obj : objects)
    {
        // Проверяем не отбракован ли объект
        if (obj.state & OBJECT_STATE_CULLED)
            continue;

        // Обрабатываем каждый многоугольник каркаса
        for (Triangle &pol : obj.polygons)
        {
            // Проверка на корректность
            if ( // Если полигон НЕ активный
                    (!(pol.state & POLYGON_STATE_ACTIVE)) // или
                    || // уже отсеченный
                    (pol.state & POLYGON_STATE_CLIPPED) // или
                    || // двухсторонний(объект прозрачный, т.е. его задняя часть видна)
                    (pol.state & POLYGON_ATTR_2SIDED) // или
                    || // признанный невидимым(задней частью)
                    (pol.state & POLYGON_STATE_BACKFACE)
               )
            { //То пропускаем этот полигон
                continue;
            }

            // Нормаль
            n = pol.normalTrans();

            // Получаем точку плоскости - она же
            // начало вектора нормали
            p0 = obj.vertex_trans[pol.indexes_vert[0]];

            // Вектор направленный от начала
            // вектора нормали в точку камеры
            view = Vector(p0, camera.position);

            // Скалярное произведение
            dp = Vector::scalarMultiplication(n, view);

            // Если оно > 0, то поверхность считается видимой,
            // если = 0 - это злая шутка, а если < 0, то
            // поверхность невидима
            if (dp <= 0.0) // проверка с 0 не сработает...
            {
                SET_BIT(pol.state,
                        POLYGON_STATE_BACKFACE);
            }
        }
    }
}

int find_dst(Point p1, Point p2)
{
    return sqrt(pow((p2.x - p1.x),2) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
}

void ObjectList::camToAxonometricAndScreenObject(const Camera &cam)
{
    // ПРИМЕЧАНИЕ. В этой функции не используются матрицы.
    // Функция преобразует объект, заданный в координатах
    // камеры, в экранные координаты на основе параметров
    // камеры. Функция работает только с вершинами,
    // содержащимися в массиве vlist_trans[}. Кроме прочего,
    // функция меняет направление оси у, поэтому
    // генерируемые ею координаты являются экранными,
    // готовыми для визуализации


    // Примечание он пишет что матрицами не так производительно
    //double alpha = (0.5 * cam.viewplane_width - 0.5);
    //double beta = (0.5 * cam.viewplane_height - 0.5);

    // нужно обсуждение, но...

    double alpha = (0.5 * cam.viewport_w - 0.5);
    double beta = (0.5 * cam.viewport_h - 0.5);
    int dst = cam.dst;
    // Добавил чтобы работало

    std::cout << "\nalpha " << cam.viewplane_width << ", beta " <<
                cam.viewplane_height << ", cam->dst " << cam.dst;

    double z;

    for (Object &obj : objects)
    {
        for (Point &point : obj.vertex_trans)
        {
            z = point.z;

            //obj->vertex_trans[i].x = cam->view_dst_hor * obj->vertex_trans[i].x / z;
            //obj->vertex_trans[i].y =  cam->view_dst_ver * obj->vertex_trans[i].y * cam->asp_ratio / z;
            // пока не понял откуда берутся view_dst_hor view_dst_ver в формуле вроде только dist
            // to axon
            if (fabs(z) > 0.00001)
            {
                point.x = 100 * point.x;// / z;
                point.y = 100 * point.y * cam.asp_ratio;// / z;
            }

            // to screen
            point.x += alpha;
            point.y = -point.y + beta;
            std::cout << "EBANINA\n";
            std::cout << point << "\n";
        }
    }
}

// переопределение вывода
std::ostream& operator<<
(std::ostream& os, const ObjectList& list)
{
     os << "\n ObjectList(size" << list.size() << ")";
     for (Object obj : list.objects)
     {
         os << obj;
     }
    return os;
}
