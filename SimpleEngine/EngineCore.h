#pragma once

#include <string>
#include <type_traits>
#include <vector>
#include <entt.hpp>

#include "Renderer.h"
#include "Collisions/CollisionsDetector.h"
#include "Memory/MemoryPool.h"

class GameObject;

class GameObjectComponent;

class EngineCore
{
private:
	Vector2 windowSize{};
	Renderer renderer{};
	MemoryPool pool{};
	CollisionsDetector collisionsDetector{};
	entt::registry registry;

	inline static EngineCore* Instance = nullptr;

	entt::dense_map<entt::entity, entt::type_info> OnCreateComponents;
	entt::dense_map<entt::entity, entt::type_info> OnUpdateComponents;
	entt::dense_map<entt::entity, entt::type_info> OnDestroyComponents;
public:
	static EngineCore* GetInstance();

	Vector2 GetWindowSize() const;

	void Run();

	GameObject* CreateGameObject();

	GameObject* CreateGameObject(const std::string& name);

	template<typename T>
	T* GetComponent(const GameObject* owner) const;

	template<typename T>
	void GetComponents(const GameObject* owner, std::vector<T*>& result) const;

	template<typename T>
	requires std::is_base_of_v<GameObjectComponent, T>
	T* AddComponent(GameObject* owner);

	bool IsValid(GameObject* object) const;

	bool IsValid(GameObjectComponent* component);

	void Destroy(GameObject* object);

	[[nodiscard]] size_t GetComponentsCount() const;

	[[nodiscard]] size_t GetGameObjectsCount() const;

	template<typename T>
	void SubscribeToOnCreate(entt::entity Entity);

	template<typename T>
	void UnSubscribeFromOnCreate(entt::entity Entity);

	template<typename T>
	void SubscribeToUpdate(entt::entity Entity);

	template<typename T>
	void UnSubscribeFromUpdate(entt::entity Entity);

	template<typename T>
	void SubscribeToOnDestroy(entt::entity Entity);

	template<typename T>
	void UnSubscribeFromOnDestroy(entt::entity Entity);

	template<typename T>
	T& AddComponent(entt::entity Entity);

	template<typename T>
	T& GetComponent(entt::entity Entity);

	template<typename T>
	void RemoveComponent(entt::entity Entity);

private:
	EngineCore() = default;

	void DestroyObjects();

	void UpdateCollisions();
};
