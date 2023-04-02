#include "CameraStatsComponent.h"

#include <format>

#include "GameObject.h"
#include "Logger.h"
#include "Components/Camera2dComponent.h"
#include "Components/TransformComponent.h"
#include "Input/Input.h"

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

    if (IsKeyPressed(Input::DebugKey))
        IsActivated = !IsActivated;

    if (!IsActivated)
        return;

    int componentsCount = EngineCore::GetInstance()->GetComponentsCount();
    int gameobjectsCount = EngineCore::GetInstance()->GetGameObjectsCount();
    float fps = GetFPS();
    auto cameraPosition = transformComponent->GetWorldPosition();
    std::string message = std::format("--Game stats--\n"
                                      "Components count: {}\n"
                                      "GameObjects count: {}\n"
                                      "World Position X:{} Y:{}\n"
                                      "Zoom:{}\n"
                                      "FPS: {}",
                                      componentsCount, gameobjectsCount, cameraPosition.x, cameraPosition.y,
                                      cameraComponent->GetZoom(), fps);
    DrawText(message.c_str(), 30, 30, 40, LIGHTGRAY);
}
