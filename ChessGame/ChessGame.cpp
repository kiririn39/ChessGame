#pragma once

#include "GameObjectTemplates.h"
#include "Components/EngineStatsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"


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

    engine->Run();
}
