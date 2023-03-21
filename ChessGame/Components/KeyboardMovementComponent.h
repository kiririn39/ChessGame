#pragma once
#include "Components/GameObjectComponent.h"

class KeyboardMovementComponent : public GameObjectComponent
{
public:
    void OnUpdate(float deltaTime) override;
};
