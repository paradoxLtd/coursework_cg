#include "objectlist.h"
#include <qDebug>
void ObjectList::copy(ObjectList list)
{
   this->objects = list.objects;
}

ObjectList::ObjectList(const ObjectList &list)
{
    copy(list);
}

ObjectList::ObjectList(ObjectList &&list)
{
    copy(list);
    list.objects.clear();
}

ObjectList& ObjectList::operator=(const ObjectList& list)
{
    copy(list);
};

ObjectList& ObjectList::operator=(ObjectList&& list)
{
    copy(list);
    list.objects.clear();
}

// Заведомо сюда не включены преобразования для
// точек текстур, ТОЛЬКО ДЛЯ ВЕРШИН
void ObjectList::prepareForConveyor(MoveOptions mop,
                                    RotateOptions rop,
                                    ScaleOptions sop)
{
    for (Object obj : objects)
    {
        // обновление радиусов, сброс статусов(отсечен)
        // копирование исходных массивов в основные
        obj.update();
        // преобразования над трансформированными координатами
        for (Point point : obj.vertex_trans)
        {
            Transformation::fullTransform(point,
                                          mop, rop,
                                          sop);
        }
    }
}

void ObjectList::push(Object &obj)
{
   objects.push_back(obj);
   size++;
}

void ObjectList::localToWorld()
{
    Point point_tmp;
    for (Object obj : objects)
    {
        obj.vertex_trans.clear();
        for (Point point : obj.vertex_trans)
        {
            point_tmp = Point(point.x + obj.center.x,
                point.y + obj.center.y, point.z + obj.center.z, point.w);
            obj.vertex_trans.push_back(point_tmp);
        }
    }
}

void ObjectList::worldToCam(Camera &cam)
{
    cam.build_cam_matrix();

    for (Object obj : objects)
    {
        for (Point point : obj.vertex_trans)
        {
            point = Matrix::multiplicate(old, cam.mcam);
        }

        for (Point point : texture_coords)
        {
            point = Matrix::multiplicate(old, cam.mcam);
        }

        for (Point point : texture_coords_trans)
        {
            point = Matrix::multiplicate(old, cam.mcam);
        }

        obj.center = Matrix::multiplicate(obj.center, cam.mcam);
        obj.dir = Matrix::multiplicate(obj.dir, cam.mcam);
        obj.ux = Matrix::multiplicate(obj.ux, cam.mcam);
        obj.uy = Matrix::multiplicate(obj.uy, cam.mcam);
        obj.uz = Matrix::multiplicate(obj.uz, cam.mcam);
    }
}

// Проверка необходимости отсечения по плоскости Z
bool ObjectList::cutZ(int culL_flags, Point &sphere,
                      Object &obj, const Camera &camera)
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
bool ObjectList::cutX(int culL_flags, Point &sphere,
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
bool ObjectList::cutY(int culL_flags, Point &sphere,
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

void ObjectList::removeObject(int culL_flags,
                              const Camera &camera)
{
    // Центр объекта в координатах камеры
    Point sphere_center;

    // Проход по всем объектам
    for (Object obj : objects)
    {
        // Получаем центр объекта и расстояние до наиболее
        // удаленной точке, принимаемое за радиус окружности
        // sphere_center = camera.cameraTransformation(obj.center);

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

    // Итератор движения по списку вершин
    std::list<Point>::iterator it;

    // Вектор нормали и вектор, направленный в точку наблюдения
    Vector n, view;

    // Хранит результат скалярного произведения
    double dp;

    // Обрабатываем каждый объект сцены
    for (Object obj : objects)
    {
        // Проверяем не отбракован ли объект
        if (obj.state & OBJECT_STATE_CULLED)
            continue;

        // Обрабатываем каждый многоугольник каркаса
        for (Triangle pol : obj.polygons)
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

void ObjectList::camToAxonometricAndScreenObject(Object *obj, Camera *cam)
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
    float alpha = (0.5 * cam->viewplane_width - 0.5);
    float beta = (0.5 * cam->viewplane_height - 0.5);

    int vsize = obj->vertex_trans.size();
    qDebug() << obj->vertex_trans[0].x << " " << obj->vertex_trans[0].y << " " << obj->vertex_trans[0].z;
    qDebug() << obj->vertex_trans[1].x << " " << obj->vertex_trans[1].y << " " << obj->vertex_trans[1].z;
    qDebug() << obj->vertex_trans[2].x << " " << obj->vertex_trans[2].y << " " << obj->vertex_trans[2].z;

    for (int i = 0; i < vsize; i++)
    {

        double z = obj->vertex_trans[i].z;
        //obj->vertex_trans[i].x = cam->view_dst_hor * obj->vertex_trans[i].x / z;
        //obj->vertex_trans[i].y =  cam->view_dst_ver * obj->vertex_trans[i].y * cam->asp_ratio / z;
        // пока не понял откуда берутся view_dst_hor view_dst_ver в формуле вроде только dist
        // to axon
        if (z != 0)
        {
            obj->vertex_trans[i].x = cam->dst * obj->vertex_trans[i].x / z;
            obj->vertex_trans[i].y =  cam->dst * obj->vertex_trans[i].y * cam->asp_ratio / z;
        }

        // to screen
        obj->vertex_trans[i].x += alpha;
        obj->vertex_trans[i].y = -obj->vertex_trans[i].y + beta;
        qDebug() << obj->vertex_trans[i].x << " " << obj->vertex_trans[i].y << " " << obj->vertex_trans[i].z;
    }
}
