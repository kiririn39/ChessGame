#pragma once

#include <string>
#include <type_traits>
#include <vector>
#include <entt.hpp>

#include "Renderer.h"
#include "Collisions/CollisionsDetector.h"
#include "Memory/MemoryPool.h"
#include "GameEntities/GameEntity.h"
#include "GameEntities/GameComponent.h"

class GameObject;

class GameObjectComponent;

class EngineCore
{
 public:
	static EngineCore* GetInstance();

	Vector2 GetWindowSize() const;

	void Run();

	GameEntity CreateEntity(const std::string& name = "");

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

	size_t GetComponentsCount() const;

	size_t GetGameObjectsCount() const;

	template<typename T>
	void SubscribeToOnCreate(GameEntity entity);

	template<typename T>
	void UnSubscribeFromOnCreate(GameEntity entity);

	template<typename T>
	void SubscribeToUpdate(GameEntity entity);

	template<typename T>
	void UnSubscribeFromUpdate(GameEntity entity);

	template<typename T>
	void SubscribeToOnDestroy(GameEntity entity);

	template<typename T>
	void UnSubscribeFromOnDestroy(GameEntity entity);

	template<typename T>
	T& AddComponent(GameEntity entity);

	template<typename T>
	T& GetComponent(GameEntity entity);

	template<typename T>
	void RemoveComponent(GameEntity entity);

	bool IsValid(GameEntity entity);

	template<typename T>
	bool IsValid(GameEntity entity);

 private:
	EngineCore() = default;

	void DestroyObjects();

	void UpdateCollisions();

 public:
	entt::registry registry;

 private:
	Vector2 windowSize{};
	Renderer renderer{};
	MemoryPool pool{};
	CollisionsDetector collisionsDetector{};

	inline static EngineCore* Instance = nullptr;

	entt::dense_map<entt::entity, entt::type_info> OnCreateComponents;
	entt::dense_map<entt::entity, entt::type_info> OnUpdateComponents;
	entt::dense_map<entt::entity, entt::type_info> OnDestroyComponents;
};
