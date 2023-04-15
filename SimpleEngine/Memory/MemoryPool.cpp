#include "MemoryPool.h"

#include "GameObject.h"
#include <algorithm>

MemoryPool::MemoryPool()
{
	typesVectors.reserve(100);
	Components.reserve(1000);
	GameObjects.reserve(100);
}

void MemoryPool::Invalidate(GameObjectComponent* instance)
{
	instance->IsInvalid = true;

	auto newEnd = std::remove(Components.begin(), Components.end(), instance);
	Components.erase(newEnd, Components.end());
}

void MemoryPool::Invalidate(GameObject* instance)
{
	instance->isInvalid = true;

	auto newEnd = std::remove(GameObjects.begin(), GameObjects.end(), instance);
	GameObjects.erase(newEnd, GameObjects.end());
}
