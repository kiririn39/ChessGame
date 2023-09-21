#include "CameraStatsComponent.h"

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
//        Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
//                                      "CameraPositionStatsComponent can't work, Gameobject: %s has nocameraComponent or transformComponent\n",
//                                      OwnerObject->Name));
		assert(false);
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
//    std::string message = Engine::Format("--Game stats--\n"
//                                      "Components count: %i\n"
//                                      "GameObjects count: %i\n"
//                                      "World Position X:%i Y:%i\n"
//                                      "Zoom:%i\n"
//                                      "FPS: %i",
//                                      componentsCount, gameobjectsCount, cameraPosition.x, cameraPosition.y,
//                                      cameraComponent->GetZoom(), fps);
//    DrawText(message.c_str(), 30, 30, 40, LIGHTGRAY);
	assert(false);
}
