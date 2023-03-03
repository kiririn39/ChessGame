#include "EngineStatsComponent.h"

#include <raylib.h>

#include "Engine.h"

void EngineStatsComponent::OnUpdate(float deltaTime)
{
	TimeLeft -= deltaTime;

	static int componentsCount;
	static int gameObjectsCount;

	if (TimeLeft <= 0.0f)
	{
		TimeLeft = Timeout;

		const auto* engine = Engine::GetInstance();

		componentsCount = engine->GetComponentsCount();
		gameObjectsCount = engine->GetGameObjectsCount();
	}

	DrawText(TextFormat("Gameobjects:%d\nComponents:%d\nFps:%d", gameObjectsCount, componentsCount, GetFPS()), 20, 20, 20, LIGHTGRAY);
}
