#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "camera.h"
#include "transformation.h"
#include "bit.h"
#include <list>

//Общие флаги отсечения
#define CULL_OBJECT_X 0x0001// Отсечение по оси х
#define CULL_OBJECT_Y 0x0002 // Отсечение по оси у
#define CULL_OBJECT_Z 0x0004 // Отсечение по оси г
#define CULL_OBJECT_XYZ (CULL_OBJECT_X | \
CULL_OBJECT_Y| CULL_OBJECT_Z)

// плоскость
class Scene
{
private:
public:
    //HDC hdc;
    double A, B, C, D;
    std::list<Object> objects;
    Camera camera;

    int ar;  // соотношение длины и ширины
    int fov; // поле зрения, всегда 90
    int d;   // расстояние до плоскости проекции

    Scene();

    // 430
    void localToWorld();

    // 435
    void worldToCam();

    //450
    // d - расстояние до камеры
    /*
    void camToAxonometric(int d = 1)
    {
        ar ...
        for (Object obj : objects)
        {
            for (Point point : obj.vertex_trans)
            {
                point.x = d * point.x / point.z;
                point.y = d * point.y / point.z;
            }
        }
    }
    */

    // Преобразование точки из мировых координат
    // в камерные
    Point cameraTransformation(Point old);

    // Проверка необходимости отсечения по плоскости Z
    bool cutZ(int culL_flags, Point sphere, Object obj );

    // Проверка необходимости отсечения по плоскости Y
     bool cutX(int culL_flags, Point sphere, Object obj );

    // Проверка необходимости отсечения по плоскости X
    bool cutY(int culL_flags, Point sphere, Object obj );

    // Отбраковка объектов, 574
    void removeObject(int culL_flags);

    // Удаление обратных поверхностей(задняя часть куба), 580
    void removeBackSurfaces();
};

#endif // SCENE_H
