#pragma once
#include <type_traits>
#include <vector>

#include "GameObjectComponent.h"
#include "GameObject.h"



class Engine
{
public:
	static Engine* GetInstance();

	void Run();

	GameObject* CreateGameObject();

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	T* GetComponent(GameObject* owner);

	template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
	T* AddComponent(GameObject* owner);

	bool IsValid(GameObject* object) const;
	bool IsValid(GameObjectComponent* component) const;

	void Destroy(GameObject* object);

	[[nodiscard]] size_t GetComponentsCount() const;
	[[nodiscard]] size_t GetGameObjectsCount() const;

private:
	inline static Engine* Instance = nullptr;
	std::vector<GameObject*> GameObjects{};
	std::vector<GameObjectComponent*> Components{};

	Engine() = default;
	void DestroyMarkedObjects();
};

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* Engine::GetComponent(GameObject* owner)
{
	const auto match = Components | std::ranges::find_if([owner](const GameObjectComponent* component)
		{
			return component->GetOwner() == owner;
		});

	return match;
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* Engine::AddComponent(GameObject* owner)
{
	T* instance = new T();

	instance->InitializeInstance(owner);
	Components.push_back(instance);
	owner->ComponentsCount++;

	return instance;
}
