#include "SpriteComponent.h"

#include "GameObjectTemplates.h"
#include "TransformComponent.h"

void SpriteComponent::FreeTexture()
{
    UnloadTexture(texture);

    hasInitializedTexture = false;
}

void SpriteComponent::LoadSpriteFromPath(const char* path)
{
    if (hasInitializedTexture)
        FreeTexture();

    texture = LoadTexture(path);
}

void SpriteComponent::OnUpdate(float deltaTime)
{
    if (!hasInitializedTexture)
        return;
    
    auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();
    //
    // if (transform == nullptr)
    //     return;
    //
    // Vector3 scale = transform->GetLocalScale();
    //
    // Rectangle originRect = Rectangle{0, 0, (float)texture.width, (float)texture.height};
    // Rectangle destinationRect = originRect;
    //
    // destinationRect.width *= scale.x;
    // destinationRect.height *= scale.y;
    //
    // DrawTexturePro(texture, originRect, destinationRect, Vector2Zero(), transform->GetLocalRotation().z, WHITE);
}

void SpriteComponent::OnDestroy()
{
    FreeTexture();
}
