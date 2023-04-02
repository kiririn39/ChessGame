#pragma once

#include "GameObjectTemplates.h"
#include "Components/Camera2dComponent.h"
#include "Components/CameraStatsComponent.h"
#include "Components/CameraZoomComponent.h"
#include "Components/EngineStatsComponent.h"
#include "Components/KeyboardMovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "External/raylib/src/raymath.h"


int main()
{
    const auto engine = EngineCore::GetInstance();

    const auto object = engine->CreateGameObject();
    object->AddComponentOfType<EngineStatsComponent>();
    object->AddComponentOfType<TransformComponent>();

    auto spriteObject = engine->CreateGameObject("GameBoard");
    spriteObject->AddComponentOfType<TransformComponent>();
    auto spriteComponent = spriteObject->AddComponentOfType<SpriteComponent>();
    spriteComponent->LoadSpriteFromPath(R"(Resources\board_plain_04.png)");

    auto cameraObject = engine->CreateGameObject("Game Camera");
    auto cameraTransform = cameraObject->AddComponentOfType<TransformComponent>();
    cameraObject->AddComponentOfType<CameraZoomComponent>();
    cameraObject->AddComponentOfType<Camera2dComponent>()->SetZoom(6.0f);
    cameraObject->AddComponentOfType<KeyboardMovementComponent>();
    cameraObject->AddComponentOfType<CameraStatsComponent>();

    spriteObject->AddChildGameObject(cameraObject);

    auto halfSprite = Vector2Scale(spriteComponent->GetSpriteSize(), 0.5f);

    auto rook = engine->CreateGameObject("Rook");
    auto rookTransform = rook->AddComponentOfType<TransformComponent>();
    rookTransform->SetLocalPosition({10, 0, 0});
    auto rookSprite = rook->AddComponentOfType<SpriteComponent>();
    rookSprite->LoadSpriteFromPath(R"(Resources\B_Rook.png)");

    cameraTransform->SetLocalPosition({halfSprite.x, halfSprite.y, 0});
    engine->Run();
}
