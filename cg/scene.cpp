#include "scene.h"

/*Scene::Scene(QGraphicsScene* graphics_scene,
             Camera cam)
{
    this->camera = cam;
    this->drawer = Drawer(graphics_scene);
}*/

Scene::Scene(Bitmap *bitmap, Camera camera)
{
    this->camera = camera;
    this->drawer =  new Drawer(bitmap);
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
                         const ScaleOptions &sop,
                         const RotateOptions &rop)
{
    /*Transformation::fullTransform(this->camera,
                                  mop, rop, sop);*/
    this->camera.build_cam_matrix();
}

void Scene::updateScene()
{
    this->clear();
    this->draw();
}

// приведение к исходным значениям и применение преобразовний
int Scene::ready(const MoveOptions &mop,
                 const ScaleOptions &sop,
                 const RotateOptions &rop)
{
    if (this->objects.size() == 0)
        return -1;
    this->objects.prepareForConveyor(mop, sop, rop);
    return 0;
}

// проверка на ошибки
int Scene::steady()
{
    int error = 0; //Что за?

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

    this->drawer->draw_objects(this->objects);
}

void Scene::clear()
{
    this->drawer->clear();
}

// Запуск конвейера
int Scene::draw(const MoveOptions &mop,
                const ScaleOptions &sop,
                const RotateOptions &rop)
{
    if (ready(mop, sop, rop) == 0)
    {
        if (steady() == 0)
        {
            go();
            return 0;
        }
        return -1;
    }
    return -2;
}
