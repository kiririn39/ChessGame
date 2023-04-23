#pragma once

#include <entt.hpp>

struct GameEntity
{
	entt::entity Entity = entt::null;

	GameEntity() = default;

	GameEntity(entt::entity Entity)
			: Entity(Entity)
	{

	}

	operator entt::entity()
	{
		return Entity;
	}

	bool IsValid();
};