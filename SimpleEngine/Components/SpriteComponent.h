#pragma once

#include "GameObjectComponent.h"
#include "IRenderComponent.h"
#include "raylib.h"

class SpriteComponent : public GameObjectComponent, public IRenderComponent
{
private:
    Texture2D texture{};
    Image preLoadedTextureData{};
    int sortingOrder = 0;

public:
    Vector2 Offset;

    void FreeAllTextureData();
    void FinishTextureLoading();

public:
    void LoadSpriteFromPath(const char* path);

    Vector2 GetSpriteSize() const;

    void OnInitialize() override;
    void OnDestroy() override;

    void SetRenderOrder(int order);
    int GetRenderOrder() const override;
    void Render() override;
};
