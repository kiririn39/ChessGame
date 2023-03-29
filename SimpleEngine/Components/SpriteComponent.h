#pragma once

#include "GameObjectComponent.h"
#include "raylib.h"

class SpriteComponent : public GameObjectComponent
{
private:
    Texture2D texture{};
    Image preLoadedTextureData{};

    void FreeAllTextureData();
    void FinishTextureLoading();
public:
    void LoadSpriteFromPath(const char* path);

    Vector2 GetSpriteSize() const;

    void OnInitialize() override;
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;
};
