#ifndef OBJECTLIST_H
#define OBJECTLIST_H

// аналог RendertList 539
// Все действия производимые над всем всеми объектами сцены
// вынесены сюда, чтобы не засорять класс сцены
// используется именно std::list<Object>, поскольку гарантируется
// последовательная работа со всеми объектами и
// обращение по индексу использоваться не будет

#include "Object.h"
#include "Transformation.h"
#include "Camera.h"
#include "Bit.h"

//Общие флаги отсечения
// Отсечение по оси х
#define CULL_OBJECT_X 0x0001
 // Отсечение по оси у
#define CULL_OBJECT_Y 0x0002
// Отсечение по оси z
#define CULL_OBJECT_Z 0x0004
#define CULL_OBJECT_XYZ (CULL_OBJECT_X | \
CULL_OBJECT_Y| CULL_OBJECT_Z)

// Используем недеструктивную модель 538
// То есть у нас 3 действия
// 1) копирование исходного списка вершин в
// список-копию(trans)
// 2) преобразование списка-копии
// 3) передача списка-копии в 3д конвеер

class ObjectList
{
private:
    void copy(ObjectList obj);

    // Проверка необходимости отсечения по плоскости Z
    bool cutZ(int culL_flags, Point &sphere,
              Object &obj,
              const Camera &camera);

    // Проверка необходимости отсечения по плоскости Y
     bool cutX(int culL_flags, Point &sphere,
               Object &obj,
               const Camera &camera);

    // Проверка необходимости отсечения по плоскости X
    bool cutY(int culL_flags, Point &sphere,
              Object &obj, const Camera &camera);
public:
    std::list<Object> objects;

    ObjectList(std::list<Object> objs = {})
    {
        this->objects = objs;
    }

    ObjectList(const ObjectList &objects);

    ObjectList(ObjectList &&objects);

    ObjectList& operator=
        (const ObjectList& other);

    ObjectList& operator=(ObjectList&& other);

    ~ObjectList()
    {
        clear();
    }

     void push(Object &obj);

     int size();

     void clear();

    //538
    void prepareForConveyor(const MoveOptions &mop,
                            const RotateOptions &rop,
                            const ScaleOptions &sop);

    // 430
    void localToWorld();

    // 435
    // Преобразование точки из мировых
    // координат в камерные
    void worldToCam(Camera &camera);

    //450; 583
    // d - расстояние до камеры
    // Преобразование в аксонометрические
    void camToAxonometricAndScreenObject(const Camera &cam);

    // Отбраковка объектов, 574
    void removeObject(
            int culL_flags,
            const Camera &camera);

    // Удаление обратных поверхностей(задняя часть куба), 580
    void removeBackSurfaces(
            const Camera &camera);

};

#endif // OBJECTLIST_H
