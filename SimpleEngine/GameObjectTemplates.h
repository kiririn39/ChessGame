#pragma once
#include "EngineCoreTemplates.h"
#include "GameObject.h"

template <typename T>
T* GameObject::GetComponentOfType() const
{
    return EngineCore::GetInstance()->GetComponent<T>(this);
}

template <typename T>
void GameObject::GetComponentsOfType(std::vector<T*>& result) const
{
    return EngineCore::GetInstance()->GetComponents<T>(this, result);
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* GameObject::AddComponentOfType()
{
    return EngineCore::GetInstance()->AddComponent<T>(this);
}
