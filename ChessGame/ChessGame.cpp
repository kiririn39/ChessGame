#pragma once

#include "GameObjectTemplates.h"
#include "Backward/BackwardClass.h"
#include "Components/Camera2dComponent.h"
#include "Components/EngineStatsComponent.h"
#include "Components/KeyboardMovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "External/raylib/src/raymath.h"


int main()
{
    Backward::CreateInstance();

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
    auto cameraTransform = cameraObject->AddComponentOfType<TransformComponent>();
    cameraObject->AddComponentOfType<Camera2dComponent>();
    cameraObject->AddComponentOfType<KeyboardMovementComponent>();

    spriteObject->AddChildGameObject(cameraObject);

    auto halfSprite = Vector2Scale(spriteComponent->GetSpriteSize(), 0.5f);

    cameraTransform->SetLocalPosition({halfSprite.x, halfSprite.y, 0});
    engine->Run();
}
