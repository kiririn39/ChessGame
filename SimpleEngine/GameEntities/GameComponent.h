//
// Created by Vlad Boroday on 2023-04-20.
//

#pragma once

#include <type_traits>
#include <optional>
#include "GameEntity.h"

class GameComponent
{
private:
	GameEntity Entity;

public:
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameComponent, T>>>
	T& AddComponent();

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameComponent, T>>>
	void RemoveComponent();

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameComponent, T>>>
	T& GetComponent();

private:
	GameComponent(entt::entity Entity);
};