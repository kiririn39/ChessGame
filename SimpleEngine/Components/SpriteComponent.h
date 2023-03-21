#pragma once

#include "GameObjectComponent.h"
#include "raylib.h"

class SpriteComponent : public GameObjectComponent
{
private:
    bool hasInitializedTexture = false;
    const char* PathToInitialSprite = nullptr;
    Texture2D texture{};

    void FreeTexture();

    bool IsFilePathValid(const char* path) const;

public:
    void LoadSpriteFromPath(const char* path);

    void OnInitialize() override;
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;
};
