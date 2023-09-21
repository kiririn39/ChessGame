#pragma once

#include <entt.hpp>

class GameEntity
{
 public:
	GameEntity(entt::entity entity)
		: _entity(entity)
	{
	}

	operator entt::entity()
	{
		return _entity;
	}

	bool IsValid();

	template<typename T, typename... Args>
	T& AddComponent(Args&& ... args);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();

 private:
	entt::entity _entity = entt::null;

};
