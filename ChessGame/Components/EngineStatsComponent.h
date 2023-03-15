#pragma once
#include "Components/GameObjectComponent.h"

class EngineStatsComponent : public GameObjectComponent
{
private:
    const float Timeout = 1.0f;
    float TimeLeft = 0.0f;

public:
    void OnUpdate(float deltaTime) override;
};
