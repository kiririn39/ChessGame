//
// Created by Vlad Boroday on 2023-04-20.
//

#include "GameEntity.h"
#include "EngineCore.h"

bool GameEntity::IsValid()
{
	return EngineCore::GetInstance()->IsValid(*this);
}
