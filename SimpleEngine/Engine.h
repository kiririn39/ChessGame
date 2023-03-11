#pragma once
#include "EngineCore.h"
#include "GameObject.h"
#include "GameObjectComponent.h"

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* EngineCore::GetComponent(GameObject* owner)
{
    const auto match = Components | std::ranges::find_if([owner](const GameObjectComponent* component)
    {
        return component->GetOwner() == owner;
    });

    return match;
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* EngineCore::AddComponent(GameObject* owner)
{
    T* instance = new T();

    instance->InitializeInstance(owner);
    Components.push_back(instance);
    owner->ComponentsCount++;

    return instance;
}


template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* GameObject::GetComponentOfType()
{
    return EngineCore::GetInstance()->GetComponent<T>(this);
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
void GameObject::AddComponentOfType()
{
    EngineCore::GetInstance()->AddComponent<T>(this);
}
