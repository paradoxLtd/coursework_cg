#ifndef CAMERA_H
#define CAMERA_H

#include "vector4f.h"
#include "Matrix4f.h"
#include "transform.h"

//import java.awt.event.KeyEvent;


class Camera
{
public:
    // Инициализация в реализации
    static const Vector4f Y_AXIS;
    Camera() = default;
    Camera(Matrix4f projection);

    Matrix4f GetViewProjection();

    // В оригинале был Input, у нас убран
    void Update(/*Input input,*/ float delta);

    Transform GetTransform();

    void Move(Vector4f dir, float amt);

    void Rotate(Vector4f axis, float angle);

private:
    Transform m_transform;
    Matrix4f m_projection;
};

#endif // CAMERA_H
