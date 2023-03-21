#pragma once
#include "EngineCore.h"
#include "GameObject.h"
#include "Components/GameObjectComponent.h"

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* EngineCore::GetComponent(GameObject* owner)
{
    auto match = std::ranges::find_if(Components, [owner](const GameObjectComponent* component)
    {
        return component->GetOwner() == owner && dynamic_cast<const T*>(component) != nullptr;
    });

    if (match == Components.end())
        return nullptr;

    return static_cast<T*>(*match);
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
