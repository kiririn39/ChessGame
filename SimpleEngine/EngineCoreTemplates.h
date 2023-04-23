#pragma once

#include <iterator>
#include <ranges>
#include <algorithm>

#include "EngineCore.h"
#include "GameObject.h"
#include "Components/GameObjectComponent.h"
#include "Memory/MemoryPoolTemplates.h"

template<typename T>
T* EngineCore::GetComponent(const GameObject* owner) const
{
	auto match = std::ranges::find_if(pool.Components, [owner](const GameObjectComponent* component)
	{
		return component->GetOwner() == owner && dynamic_cast<const T*>(component) != nullptr;
	});

	if (match == pool.Components.end())
		return nullptr;

	return static_cast<T*>(*match);
}

template<typename T>
void EngineCore::GetComponents(const GameObject* owner, std::vector<T*>& result) const
{
	auto isTType = std::views::filter([owner](GameObjectComponent* component)
	{
		return component->GetOwner() == owner && dynamic_cast<T*>(component) != nullptr;
	});

	auto asTType = std::views::transform([](GameObjectComponent* component)
	{
		return dynamic_cast<T*>(component);
	});

	std::ranges::copy(pool.Components | isTType | asTType, std::back_inserter(result));
}

template<typename T>
requires std::is_base_of_v<GameObjectComponent, T>
T* EngineCore::AddComponent(GameObject* owner)
{
	T* instance = pool.CreateObjectOfType<T>();

	instance->InitializeInstance(owner);
	owner->ComponentsCount++;

	return instance;
}

template<typename T>
void EngineCore::SubscribeToOnCreate(GameEntity entity)
{
	OnCreateComponents.emplace(entity).first->second = entt::type_id<T>();
}


template<typename T>
void EngineCore::UnSubscribeFromOnCreate(GameEntity entity)
{
	if (OnCreateComponents.contains(entity))
		OnCreateComponents.erase(entity);
}


template<typename T>
void EngineCore::SubscribeToUpdate(GameEntity entity)
{
	OnUpdateComponents.emplace(entity).first->second = entt::type_id<T>();
}


template<typename T>
void EngineCore::UnSubscribeFromUpdate(GameEntity entity)
{
	if (OnUpdateComponents.contains(entity))
		OnUpdateComponents.erase(entity);
}


template<typename T>
void EngineCore::SubscribeToOnDestroy(GameEntity entity)
{
	OnDestroyComponents.emplace(entity).first->second = entt::type_id<T>();
}


template<typename T>
void EngineCore::UnSubscribeFromOnDestroy(GameEntity entity)
{
	if (OnDestroyComponents.contains(entity))
		OnDestroyComponents.erase(entity);
}


template<typename T>
T& EngineCore::AddComponent(GameEntity entity)
{
	return registry.emplace<T>(entity);
}


template<typename T>
T& EngineCore::GetComponent(GameEntity entity)
{
	return registry.get<T>(entity);
}

template<typename T>
void EngineCore::RemoveComponent(GameEntity entity)
{
	OnCreateComponents.erase(entity);
	OnUpdateComponents.erase(entity);
	OnDestroyComponents.erase(entity);

	registry.erase<T>(entity);
}

template<typename T>
bool EngineCore::IsValid(GameEntity entity)
{
	return IsValid(entity) && registry.all_of<T>(entity);
}



