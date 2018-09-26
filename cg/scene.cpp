#include "Scene.h"

Scene::Scene(QGraphicsScene* graphics_scene,
             Camera cam)
{
    this->camera = Camera();
    this->drawer = Drawer(graphics_scene);
}

// Очистка объектов со сцены
void Scene::clearObjects()
{
    objects.clear();
}

// Вставка объекта
void Scene::pushObject(Object &obj)
{
    objects.push(obj);
}

// Обновление положения камеры
void Scene::updateCamera(const MoveOptions &mop,
                  const RotateOptions &rop,
                  const ScaleOptions &sop)
{
    Transformation::fullTransform(this->camera,
                                  mop, rop, sop);
}

// приведение к исходным значениям и применение преобразовний
int Scene::ready(const MoveOptions &mop,
                  const RotateOptions &rop,
                  const ScaleOptions &sop)
{
    if (this->objects.size() == 0)
        return -1;
    this->objects.prepareForConveyor(mop, rop, sop);
    return 0;
}

// проверка на ошибки
int Scene::steady()
{
    int error = 0;

    return error;
}

// отрисовка
void Scene::go()
{
    this->objects.localToWorld();
    this->objects.worldToCam(this->camera);
    this->objects.camToAxonometricAndScreenObject(
                this->camera);

    this->objects.removeObject(CULL_OBJECT_XYZ,
                               this->camera);
    this->objects.removeBackSurfaces(this->camera);

    this->drawer.draw_objects(this->objects);
}

// Запуск конвейера
int Scene::draw(const MoveOptions &mop,
                 const RotateOptions &rop,
                 const ScaleOptions &sop)
{
    if (ready(mop, rop, sop) == 0)
    {
        if (steady() == 0)
        {
            std::cout << "work";
            go();
            return 0;
        }
        return -1;
    }
    return -2;
}
