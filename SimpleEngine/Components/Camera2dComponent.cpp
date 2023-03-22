#include "Camera2dComponent.h"

#include <format>

#include "TransformComponent.h"
#include "Backward/BackwardClass.h"
#include "External/raylib/src/raymath.h"

void Camera2dComponent::OnInitialize()
{
    const auto windowSize = EngineCore::GetInstance()->GetWindowSize();

    cameraOffset = Vector2Scale(windowSize, 0.5f);
}

Camera2D Camera2dComponent::GetCamera()
{
    const auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        Backward::PrintArgs(std::format("SpriteComponent can't work, Gameobject: {} has not TransformComponent",
                                        OwnerObject->Name));
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
