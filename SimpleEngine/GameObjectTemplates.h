#pragma once
#include "EngineCoreTemplates.h"
#include "GameObject.h"

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* GameObject::GetComponentOfType()
{
    return EngineCore::GetInstance()->GetComponent<T>(this);
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* GameObject::AddComponentOfType()
{
    return EngineCore::GetInstance()->AddComponent<T>(this);
}
