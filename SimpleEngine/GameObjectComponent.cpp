#include "GameObjectComponent.h"


void GameObjectComponent::InitializeInstance(GameObject* owner)
{
    OwnerObject = owner;
}

void GameObjectComponent::OnInitialize()
{
}

void GameObjectComponent::OnUpdate(float deltaTime)
{
}

void GameObjectComponent::OnDestroy()
{
}

void GameObjectComponent::Destroy()
{
    IsFlaggedForDestruction = true;
}

GameObject* GameObjectComponent::GetOwner() const
{
    return OwnerObject;
}
