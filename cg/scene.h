#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "objectlist.h"

// Сцена
class Scene
{
private:
public:
    Camera camera;
    ObjectList objects;

    Scene(Camera camera);

};

#endif // SCENE_H
