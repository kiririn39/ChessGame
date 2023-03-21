#include "SpriteComponent.h"

#include "Backward/Backward.h"
#include "GameObjectTemplates.h"
#include "raymath.h"
#include "TransformComponent.h"
#include <format>
#include <fstream>

void SpriteComponent::FreeTexture()
{
    UnloadTexture(texture);

    hasInitializedTexture = false;
}

bool SpriteComponent::IsFilePathValid(const char* path) const
{
    const std::ifstream file(path);
    return file.good();
}

void SpriteComponent::LoadSpriteFromPath(const char* path)
{
    if (!IsInitialized)
    {
        PathToInitialSprite = path;
        return;
    }

    if (hasInitializedTexture)
        FreeTexture();

    if (!IsFilePathValid(path))
        Backward::PrintArgs(path);

    texture = LoadTexture(path);
    hasInitializedTexture = true;
}

void SpriteComponent::OnInitialize()
{
    if (PathToInitialSprite == nullptr)
        return;

    LoadSpriteFromPath(PathToInitialSprite);
}

void SpriteComponent::OnUpdate(float deltaTime)
{
    if (!hasInitializedTexture)
        return;

    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform == nullptr)
    {
        Backward::PrintArgs(std::format("SpriteComponent can't work, Gameobject: {} has not TransformComponent",
                                        OwnerObject->Name));
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
    FreeTexture();
}
