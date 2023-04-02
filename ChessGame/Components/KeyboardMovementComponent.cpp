#include "KeyboardMovementComponent.h"

#include <format>
#include <raylib.h>
#include <raymath.h>

#include "GameObjectTemplates.h"
#include "Logger.h"
#include "Components/TransformComponent.h"
#include "Input/Input.h"

void KeyboardMovementComponent::OnUpdate(float deltaTime)
{
    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format(
                                      "KeyboardMovementComponent can't work, Gameobject: {} has not TransformComponent\n",
                                      OwnerObject->Name));
        return;
    }

    auto localPosition = transform->GetLocalPosition();
    auto deltaSpeed = Speed * deltaTime;

    Vector2 direction = Input::GetVector2AxisInput(Input::DirectionAxis);
    Vector2 deltaDirection = Vector2Scale(direction, deltaSpeed);

    localPosition.x += deltaDirection.x;
    localPosition.y += deltaDirection.y;

    transform->SetLocalPosition(localPosition);
}
