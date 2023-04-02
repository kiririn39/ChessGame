#pragma once

#include "GameObjectTemplates.h"
#include "Components/Camera2dComponent.h"
#include "Components/CameraStatsComponent.h"
#include "Components/CameraZoomComponent.h"
#include "Components/CollisionTestComponent.h"
#include "Components/EngineStatsComponent.h"
#include "Components/KeyboardMovementComponent.h"
#include "Components/RectangleCollisionComponent.h"
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

    auto rookObject = engine->CreateGameObject("Rook");
    auto rookTransform = rookObject->AddComponentOfType<TransformComponent>();
    rookTransform->SetLocalPosition({10, 0, 0});
    auto rookSprite = rookObject->AddComponentOfType<SpriteComponent>();
    rookSprite->LoadSpriteFromPath(R"(Resources\B_Rook.png)");
    auto rookCollision = rookObject->AddComponentOfType<RectangleCollisionComponent>();
    rookCollision->SetBounds(rookSprite->GetSpriteSize());

    auto rookObject1 = engine->CreateGameObject("Rook");
    auto rookTransform1 = rookObject1->AddComponentOfType<TransformComponent>();
    rookTransform1->SetLocalPosition({10, 0, 0});
    auto rookSprite1 = rookObject1->AddComponentOfType<SpriteComponent>();
    rookSprite1->LoadSpriteFromPath(R"(Resources\B_Rook.png)");
    auto rookCollision1 = rookObject1->AddComponentOfType<RectangleCollisionComponent>();
    rookCollision1->SetBounds(rookSprite1->GetSpriteSize());
    rookObject1->AddComponentOfType<KeyboardMovementComponent>();
    rookObject1->AddComponentOfType<CollisionTestComponent>();


    cameraTransform->SetLocalPosition({halfSprite.x, halfSprite.y, 0});
    engine->Run();
}
