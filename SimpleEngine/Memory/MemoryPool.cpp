#include "MemoryPool.h"

#include "GameObject.h"
#include "vector"
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

	erase_if(Components, [instance](GameObjectComponent* item)
	{
	  return item == instance;
	});
}

void MemoryPool::Invalidate(GameObject* instance)
{
	erase_if(GameObjects, [instance](GameObject* item)
	{
	  return item == instance;
	});
}
