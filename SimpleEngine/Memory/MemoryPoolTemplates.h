#pragma once
#include <cassert>
#include "MemoryPool.h"

template<typename T>
requires std::is_base_of_v<GameObject, T>
T* MemoryPool::CreateObjectOfType()
{
	T* result = new T();
	result->isInvalid = false;
	GameObjects.push_back(result);

	return result;
}

template<typename T>
requires std::is_base_of_v<GameObjectComponent, T>
T* MemoryPool::CreateObjectOfType()
{
	T* result = new T();
	result->IsInvalid = false;
	Components.push_back(result);

	return result;
}
