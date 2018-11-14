#include "camera.h"

Camera::Camera(Matrix4f projection) : m_projection(projection){}

Matrix4f Camera::GetViewProjection() {
    Matrix4f cameraRotation = GetTransform().GetTransformedRot().Conjugate().toRotationMatrix();
    Vector4f cameraPos = GetTransform().GetTransformedPos().Mul(-1);

    Matrix4f cameraTranslation = Matrix4f().InitTranslation(cameraPos.GetX(), cameraPos.GetY(), cameraPos.GetZ());

    return m_projection.Mul(cameraRotation.Mul(cameraTranslation));
}

// В оригинале был Input, у нас убран
void Camera::Update(/*Input input,*/ float delta) {
    // Speed and rotation amounts are hardcoded here.
    // In a more general system, you might want to have them as variables.
    // 3 final
    const float sensitivityX = 2.66f * delta;
    const float sensitivityY = 2.0f * delta;
    const float movAmt = 5.0f * delta;

    // Similarly, input keys are hardcoded here.
    // As before, in a more general system, you might want to have these as variables.
    /*
    if(input.GetKey(KeyEvent.VK_W))
        Move(GetTransform().GetRot().GetForward(), movAmt);
    if(input.GetKey(KeyEvent.VK_S))
        Move(GetTransform().GetRot().GetForward(), -movAmt);
    if(input.GetKey(KeyEvent.VK_A))
        Move(GetTransform().GetRot().GetLeft(), movAmt);
    if(input.GetKey(KeyEvent.VK_D))
        Move(GetTransform().GetRot().GetRight(), movAmt);

    if(input.GetKey(KeyEvent.VK_RIGHT))
        Rotate(Y_AXIS, sensitivityX);
    if(input.GetKey(KeyEvent.VK_LEFT))
        Rotate(Y_AXIS, -sensitivityX);
    if(input.GetKey(KeyEvent.VK_DOWN))
        Rotate(GetTransform().GetRot().GetRight(), sensitivityY);
    if(input.GetKey(KeyEvent.VK_UP))
        Rotate(GetTransform().GetRot().GetRight(), -sensitivityY);
    */
}

Transform Camera::GetTransform() {
     return m_transform;
}

void Camera::Move(Vector4f dir, float amt) {
    m_transform = m_transform.SetPos(
                GetTransform().GetPos().Add(dir.Mul(amt)));
}

void Camera::Rotate(Vector4f axis, float angle) {
    m_transform = GetTransform().Rotate(Quaternion(axis, angle));
}

const Vector4f Camera::Y_AXIS = Vector4f(0,1,0);
