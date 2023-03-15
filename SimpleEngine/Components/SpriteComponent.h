#pragma once
#include "GameObjectComponent.h"
#include "raylib.h"

class SpriteComponent : public GameObjectComponent
{
private:
    bool hasInitializedTexture = false;
    Texture2D texture{};

    void FreeTexture();

public:
    void LoadSpriteFromPath(const char* path);

    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;
};
