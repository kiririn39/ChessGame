#pragma once

#include "GameObjectTemplates.h"
#include "Components/Camera2dComponent.h"
#include "Components/EngineStatsComponent.h"
#include "Components/KeyboardMovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"


int main()
{
    const auto engine = EngineCore::GetInstance();

    const auto object = engine->CreateGameObject();
    object->AddComponentOfType<EngineStatsComponent>();
    object->AddComponentOfType<TransformComponent>();

    auto spriteObject = engine->CreateGameObject("GameBoard");
    auto spriteTransform = spriteObject->AddComponentOfType<TransformComponent>();
    spriteTransform->SetLocalScale({3, 3, 3});
    auto spriteComponent = spriteObject->AddComponentOfType<SpriteComponent>();
    spriteComponent->LoadSpriteFromPath(R"(Resources\board_plain_04.png)");

    auto cameraObject = engine->CreateGameObject("Game Camera");
    cameraObject->AddComponentOfType<TransformComponent>();
    cameraObject->AddComponentOfType<Camera2dComponent>();
    cameraObject->AddComponentOfType<KeyboardMovementComponent>();

    engine->Run();
}
