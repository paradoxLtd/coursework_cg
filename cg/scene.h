#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "objectlist.h"
#include "drawer.h"
#include "bitmap.h"

// Сцена
class Scene
{
private:
    int ready(const MoveOptions &mop,
              const ScaleOptions &sop,
              const RotateOptions &rop);
    int steady();
    void go();

    void clear();
public:
    Camera camera;
    ObjectList objects;
    Drawer* drawer;

    // Из конструктора убрана инициализация ObjectList
    // Все равно готовый ObjectList никто кидать не будет
    // + загрузчик загружает не в ObjectList, а в сцену
    // + конструктор ObjectList вызывает краш программы...
    /*Scene(QGraphicsScene* graphics_scene = nullptr,
          Camera camera = Camera());*/

    Scene() = default;
    Scene(Bitmap *bitmap, Camera camera = Camera());


    ~Scene()
    {
        this->clearObjects();
    }

    // Примечание
    // Такой порядок(move, scale, rotate) сделан в связи
    // с простотой задания настроек. можно запилить
    // перемещение объекта, не указывая масштабирование и
    // поворот или указать только перемещение и масштабирование
    int draw(const MoveOptions &mop = MoveOptions(),
             const ScaleOptions &sop = ScaleOptions(),
             const RotateOptions &rop = RotateOptions());

    void pushObject(Object &obj);

    // Обновление положения камеры.
    void updateCamera(const MoveOptions &mop = MoveOptions(),
                      const ScaleOptions &sop = ScaleOptions(),
                      const RotateOptions &rop = RotateOptions()
                       );

    void updateScene();

    void clearObjects();

};

#endif // SCENE_H
