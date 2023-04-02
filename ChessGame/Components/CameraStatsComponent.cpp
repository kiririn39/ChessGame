#include "CameraStatsComponent.h"

#include <format>

#include "GameObject.h"
#include "Logger.h"
#include "Components/Camera2dComponent.h"
#include "Components/TransformComponent.h"

void CameraStatsComponent::OnUpdate(float deltaTime)
{
    const auto* cameraComponent = GetOwner()->GetComponentOfType<Camera2dComponent>();
    const auto* transformComponent = GetOwner()->GetComponentOfType<TransformComponent>();

    if (cameraComponent == nullptr || transformComponent == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format(
                                      "CameraPositionStatsComponent can't work, Gameobject: {} has nocameraComponent or transformComponent\n",
                                      OwnerObject->Name));
        return;
    }

    if (IsKeyPressed(KEY_APOSTROPHE))
        IsActivated = !IsActivated;

    if (!IsActivated)
        return;

    auto cameraPosition = transformComponent->GetWorldPosition();
    std::string message = std::format("--Camera stats--\n"
                                      "World Position X:{} Y:{}\n"
                                      "Zoom:{}", cameraPosition.x, cameraPosition.y, cameraComponent->GetZoom());
    DrawText(message.c_str(), 30, 30, 40, LIGHTGRAY);
}
