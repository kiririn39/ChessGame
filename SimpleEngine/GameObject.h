#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>

class GameObjectComponent;
class Engine;

class GameObject
{
private:
	uint16_t ComponentsCount{};

	GameObject* Parent = nullptr;
	std::vector<GameObject*> Children{};

	friend class Engine;

public:
	virtual ~GameObject() = default;

	void Destroy();

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	T* GetComponentOfType();

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	void AddComponentOfType();

	void AddChildGameObject(GameObject* object);
	void RemoveChildGameObject(GameObject* object);
	[[nodiscard]] GameObject* GetChildGameObject(uint16_t index) const;
	[[nodiscard]] size_t GetChildrenCount() const;
	[[nodiscard]] GameObject* GetParent() const;
	[[nodiscard]] auto GetChildren() const;
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

