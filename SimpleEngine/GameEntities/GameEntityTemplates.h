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
	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.emplace<T>(_entity, std::forward<Args>(args)...);
}

template<typename T>
T& GetComponent()
{
	if (!HasComponent<T>()){
		//Logger::LogWithStackTrace(String::)
	}
	EngineCore* engine = EngineCore::GetInstance();
	
	//return engine->registry.get<T>(_entity);
}

template<typename T>
bool GameEntity::HasComponent()
{
	EngineCore* engine = EngineCore::GetInstance();

	return engine->registry.all_of<T>(_entity);
}
#endif //CHESSGAME_SIMPLEENGINE_GAMEENTITIES_GAMEENTITYTEMPLATES_H_
