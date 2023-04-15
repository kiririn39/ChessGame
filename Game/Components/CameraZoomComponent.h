#pragma once
#include "Components/GameObjectComponent.h"

class CameraZoomComponent : public GameObjectComponent
{
public:
    void OnUpdate(float deltaTime) override;
};
