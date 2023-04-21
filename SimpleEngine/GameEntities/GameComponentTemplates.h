//
// Created by Vlad Boroday on 2023-04-22.
//

#pragma once


#include "GameComponent.h"
#include "Logger.h"
#include "EngineCore.h"
#include "Utilities/EngineTypeChecking.h"

template<typename T, typename>
T& GameComponent::AddComponent()
{
	if constexpr (!std::is_base_of_v<GameComponent, T>)
	{
		Logger::LogWithStackTrace(Level::LOG_ERROR, "You have tried to create non Component based componet");
		assert(false);
	}

	T& Result = EngineCore::GetInstance()->AddComponent<T>(Entity);

	if constexpr (HasCreatedMethod<T>())
		EngineCore::GetInstance()->SubscribeToOnCreate<T>(Entity);

	if constexpr (HasUpdateMethod<T>())
		EngineCore::GetInstance()->SubscribeToUpdate<T>(Entity);

	if constexpr (HasOnDestroyMethod<T>())
		EngineCore::GetInstance()->SubscribeToOnDestroy<T>(Entity);

	return Result;
}

template<typename T, typename>
void GameComponent::RemoveComponent()
{
	EngineCore::GetInstance()->RemoveComponent<T>(Entity);
}

template<typename T, typename>
T& GameComponent::GetComponent()
{
	return EngineCore::GetInstance()->GetComponent<T>(Entity);
}
