#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "objectlist.h"
#include "drawer.h"

// Сцена
class Scene
{
private:
    int ready(const MoveOptions &mop,
               const RotateOptions &rop,
               const ScaleOptions &sop);
    int steady();
    void go();
public:
    Camera camera;
    ObjectList objects;
    Drawer drawer;

    // Из конструктора убрана инициализация ObjectList
    // Все равно готовый ObjectList никто кидать не будет
    // + загрузчик загружает не в ObjectList, а в сцену
    // + конструктор ObjectList вызывает краш программы...
    Scene(QGraphicsScene* graphics_scene = nullptr,
          Camera camera = Camera());

    ~Scene()
    {
        this->clearObjects();
    }

    int draw(const MoveOptions &mop = MoveOptions(),
             const RotateOptions &rop = RotateOptions(),
             const ScaleOptions &sop = ScaleOptions());

    void pushObject(Object &obj);

    // Обновление положения камеры
    void updateCamera(const MoveOptions &mop,
                       const RotateOptions &rop,
                       const ScaleOptions &sop);

    void clearObjects();

};

#endif // SCENE_H
