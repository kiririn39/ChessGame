#include "KeyboardMovementComponent.h"

#include <format>
#include <raylib.h>

#include "GameObjectTemplates.h"
#include "Backward/BackwardClass.h"
#include "Components/TransformComponent.h"

void KeyboardMovementComponent::OnUpdate(float deltaTime)
{
    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        Backward::PrintArgs(std::format(
            "KeyboardMovementComponent can't work, Gameobject: {} has not TransformComponent",
            OwnerObject->Name));
        return;
    }

    auto localPosition = transform->GetLocalPosition();
    auto deltaSpeed = Speed * deltaTime;

    if (IsKeyDown(KEY_RIGHT))
        localPosition.x += deltaSpeed;
    if (IsKeyDown(KEY_LEFT))
        localPosition.x -= deltaSpeed;
    if (IsKeyDown(KEY_UP))
        localPosition.y -= deltaSpeed;
    if (IsKeyDown(KEY_DOWN))
        localPosition.y += deltaSpeed;

    transform->SetLocalPosition(localPosition);
}
