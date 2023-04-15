#pragma once
#include "Components/UIComponent.h"

class CameraStatsComponent : public UIComponent
{
private:
    bool IsActivated = false;

public:
    void OnUpdate(float deltaTime) override;
};
