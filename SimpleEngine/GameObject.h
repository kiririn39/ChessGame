#pragma once
#include <cstdint>
#include <type_traits>

class GameObjectComponent;
class Engine;

class GameObject
{
private:
	uint16_t ComponentsCount{};
	friend class Engine;

public:
	virtual ~GameObject() = default;

	void Destroy();

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	T* GetComponentOfType();

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	void AddComponentOfType();
};

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* GameObject::GetComponentOfType()
{
	return Engine::GetInstance()->GetComponent<T>(this);
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
void GameObject::AddComponentOfType()
{
	Engine::GetInstance()->AddComponent<T>(this);
}

