#include "camera.h"
#include "scene.h"

void Camera::debug()
{
    Scene scene;
    scene.camera.build_cam_matrix();
    std::cout <<  scene.camera.mcam;
    scene.updateCamera(MoveOptions(100,100,100));
    scene.camera.build_cam_matrix();
    std::cout <<  scene.camera.position;
    std::cout <<  scene.camera.mcam;
}
