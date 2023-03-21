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

    if (IsKeyDown(KEY_RIGHT))
        localPosition.x += 2.0f;
    if (IsKeyDown(KEY_LEFT))
        localPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP))
        localPosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
        localPosition.y += 2.0f;

    transform->SetLocalPosition(localPosition);
}
