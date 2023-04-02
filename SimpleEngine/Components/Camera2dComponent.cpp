#include "Camera2dComponent.h"

#include <format>
#include "Logger.h"
#include "TransformComponent.h"
#include "External/raylib/src/raymath.h"

void Camera2dComponent::OnInitialize()
{
    const auto windowSize = EngineCore::GetInstance()->GetWindowSize();

    cameraOffset = Vector2Scale(windowSize, 0.5f);
}

Camera2D Camera2dComponent::GetCamera()
{
    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format(
                                      "GameObject: {} Camera2dComponent can't work, Gameobject: {} has not TransformComponent\n",
                                      OwnerObject->Name, OwnerObject->Name));

        return Camera2D();
    }

    const auto localPosition = transform->GetLocalPosition();

    Camera2D camera;
    camera.offset = cameraOffset;
    camera.zoom = zoom;
    camera.rotation = transform->GetLocalRotation().z;
    camera.target.x = localPosition.x;
    camera.target.y = localPosition.y;

    return camera;
}

void Camera2dComponent::SetZoom(float zoom)
{
    this->zoom = zoom;
}

float Camera2dComponent::GetZoom() const
{
    return zoom;
}
