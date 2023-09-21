//
// Created by Vlad Boroday on 2023-09-19.
//

#ifndef CHESSGAME_SIMPLEENGINE_GAMEENTITIES_GAMEENTITYTEMPLATES_H_
#define CHESSGAME_SIMPLEENGINE_GAMEENTITIES_GAMEENTITYTEMPLATES_H_

#include "GameEntity.h"
#include "EngineCore.h"
#include "Logger.h"

template<typename T, typename... Args>
T& GameEntity::AddComponent(Args&& ... args)
{
	if (HasComponent<T>())
	{
		//Logger::LogWithStackTrace(String::)
		assert(0);
	}

	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.emplace<T>(_entity, std::forward<Args>(args)...);
}

template<typename T>
bool GameEntity::RemoveComponent()
{
	if (!HasComponent<T>())
	{
		//Logger::LogWithStackTrace(String::)
		assert(0);
	}
	
	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.remove<T>(_entity);
}

template<typename T>
bool GameEntity::HasComponent()
{
	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.all_of<T>(_entity);
}

template<typename T>
T& GameEntity::GetComponent()
{
	if (!HasComponent<T>())
	{
		//Logger::LogWithStackTrace(String::)
		assert(0);
	}
	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.get<T>(_entity);
}
#endif //CHESSGAME_SIMPLEENGINE_GAMEENTITIES_GAMEENTITYTEMPLATES_H_
