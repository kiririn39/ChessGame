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

GameObject* GameObjectComponent::GetOwner() const
{
	return OwnerObject;
}
