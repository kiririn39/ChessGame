#include "SpriteComponent.h"

#include "Backward/Backward.h"
#include "GameObjectTemplates.h"
#include "raymath.h"
#include "TransformComponent.h"
#include <format>
#include <sstream>

void SpriteComponent::FreeAllTextureData()
{
    UnloadTexture(texture);

    if (preLoadedTextureData.data != nullptr)
        UnloadImage(preLoadedTextureData);
}

void SpriteComponent::FinishTextureLoading()
{
    if (preLoadedTextureData.data == nullptr)
        return;

    texture = LoadTextureFromImage(preLoadedTextureData);

    UnloadImage(preLoadedTextureData);
    preLoadedTextureData.data = nullptr;
}

void SpriteComponent::LoadSpriteFromPath(const char* path)
{
    if (!FileExists(path))
    {
        TraceLog(LOG_WARNING, std::format(
                     "GameObject: {} SpriteComponent can't work, Can't load a texture from given path as it doesn't exist: {}\n{}",
                     OwnerObject->Name, path, Backward::GetTrace().str()).c_str());
        return;
    }

    FreeAllTextureData();

    preLoadedTextureData = LoadImage(path);

    texture.width = preLoadedTextureData.width;
    texture.height = preLoadedTextureData.height;
    texture.format = preLoadedTextureData.format;
    texture.mipmaps = preLoadedTextureData.mipmaps;

    if (IsInitialized)
        FinishTextureLoading();
}

Vector2 SpriteComponent::GetSpriteSize() const
{
    return Vector2(texture.width, texture.height);
}

void SpriteComponent::OnInitialize()
{
    FinishTextureLoading();
}

void SpriteComponent::OnUpdate(float deltaTime)
{
    TraceLog(LOG_WARNING,
         std::format("GameObject: {} SpriteComponent can't work, texture id == 0\n",
                     OwnerObject->Name).c_str());
    Backward::PrintTrace();
    if (texture.id == 0)
    {


        return;
    }

    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        TraceLog(LOG_WARNING, std::format(
                     "GameObject: {} SpriteComponent can't work, Gameobject: {} has not TransformComponent\n",
                     OwnerObject->Name, OwnerObject->Name).c_str());
        Backward::PrintTrace();
        return;
    }

    Vector3 scale = transform->GetLocalScale();
    Vector3 localPosition = transform->GetLocalPosition();

    Rectangle originRect = Rectangle{0, 0, (float)texture.width, (float)texture.height};
    Rectangle destinationRect = originRect;

    destinationRect.width *= scale.x;
    destinationRect.height *= scale.y;
    destinationRect.x = localPosition.x;
    destinationRect.y = localPosition.y;

    DrawTexturePro(texture, originRect, destinationRect, Vector2Zero(), transform->GetLocalRotation().z, WHITE);
}

void SpriteComponent::OnDestroy()
{
    FreeAllTextureData();
}
