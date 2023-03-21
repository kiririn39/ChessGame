#pragma once
#include "Components/GameObjectComponent.h"

class KeyboardMovementComponent : GameObjectComponent
{
public:
    void OnUpdate(float deltaTime) override;
};
