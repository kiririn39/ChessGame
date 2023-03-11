#pragma once
#include <Engine.h>
#include <Components/EngineStatsComponent.h>


int main()
{
    const auto engine = EngineCore::GetInstance();

    const auto object = engine->CreateGameObject();
    object->AddComponentOfType<EngineStatsComponent>();

    engine->Run();
}
