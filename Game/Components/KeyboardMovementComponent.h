#pragma once
#include "Components/GameObjectComponent.h"

class KeyboardMovementComponent : public GameObjectComponent
{
public:
    float Speed = 100.0f;

public:
    void OnUpdate(float deltaTime) override;
};
