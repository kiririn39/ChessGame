#pragma once

#include <entt.hpp>

struct GameEntity
{
	entt::entity Entity;

	GameEntity() = default;

	GameEntity(entt::entity Entity)
			: Entity(Entity)
	{

	}

	operator entt::entity()
	{
		return Entity;
	}
};