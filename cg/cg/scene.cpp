#include "Scene.h"

void Scene::localToWorld()
{
    Point point_tmp;
    for (Object obj : objects)
    {
        obj.vertex_trans.clear();
        for (Point point : obj.vertex_local)
        {
            point_tmp = Point(point.x + obj.center.x,
                point.y + obj.center.y, point.z + obj.center.z, point.w);
            obj.vertex_trans.push_back(point_tmp);
        }
    }
}

Point Scene::cameraTransformation(Point old)
{
    // Копия точки
    Point ret(old);

    // Создаем настроки для преобразования точки
    Rotate rotate;
    RotateOptions ropX(AXIS_X, camera.ang_x, true);
    RotateOptions ropY(AXIS_Y, camera.ang_y, true);
    RotateOptions ropZ(AXIS_Z, camera.ang_z, true);

    MoveOptions mop(camera.point, true);
    Move move;

    // Применяем матрицы преобразований
    Transformation::apply(ret, move, mop);
    Transformation::apply(ret, rotate, ropY);
    Transformation::apply(ret, rotate, ropX);
    Transformation::apply(ret, rotate, ropZ);

    return ret;
}

void Scene::worldToCam()
{
    Rotate rotate;
    RotateOptions ropX(AXIS_X, camera.ang_x, true);
    RotateOptions ropY(AXIS_Y, camera.ang_y, true);
    RotateOptions ropZ(AXIS_Z, camera.ang_z, true);

    MoveOptions mop(camera.point, true);
    Move move;

    for (Object obj : objects)
    {
        for (Point point : obj.vertex_trans)
        {
            point = Point(point.x - camera.point.x,
                point.y - camera.point.y, point.z - camera.point.z, point.w);

            //YXZ поворот 437
            Transformation::apply(point, move, mop);
            Transformation::apply(point, rotate, ropY);
            Transformation::apply(point, rotate, ropX);
            Transformation::apply(point, rotate, ropZ);
        }
    }
    Transformation::apply(camera.point, move, mop);
    Transformation::apply(camera.point, rotate, ropY);
    Transformation::apply(camera.point, rotate, ropX);
    Transformation::apply(camera.point, rotate, ropZ);
}

Scene::Scene()
{
    this->ar = 1;
    this->fov = 90;
    this->d = 1;
}

// Проверка необходимости отсечения по плоскости Z
bool Scene::cutZ(int culL_flags, Point sphere, Object obj )
{
    // Координаты плоскостей отсечения камеры
    double farZ = camera.far_clip_z;
    double nearZ = camera.near_clip_z;

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
bool Scene::cutX(int culL_flags, Point sphere, Object obj )
{
    // Радиус сферы
    double rad = obj.max_radius;

    // Ширина обзора камеры и дистанция до плоскости
    double width = camera.viewplane_width;
    double dist = camera.view_dist;

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
bool Scene::cutY(int culL_flags, Point sphere, Object obj )
{
    // Радиус сферы
    double rad = obj.max_radius;

    // Высота обзора камеры и дистанция до плоскости
    double height = camera.viewplane_height;
    double dist = camera.view_dist;

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

void Scene::object_culling(int culL_flags)
{
    // Центр объекта в координатах камеры
    Point sphere_center;

    // Проход по всем объектам
    for (Object obj : objects)
    {
        // Получаем центр объекта и расстояние до наиболее
        // удаленной точке, принимаемое за радиус окружности
        sphere_center = cameraTransformation(obj.center);

        // Отбраковываем по оси z
        if (cutZ(culL_flags, sphere_center, obj))
            continue;

        // Отбраковываем по оси x
        if (cutX(culL_flags, sphere_center, obj))
            continue;

        // Отбраковываем по оси y
        if (cutY(culL_flags, sphere_center, obj))
            continue;

    }
}
