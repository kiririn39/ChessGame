#include "Engine.h"

#include <raylib.h>
#include <ranges>

Engine* Engine::GetInstance()
{
	if (Instance == nullptr)
		Instance = new Engine();

	return Instance;
}

void Engine::Run()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		const float deltaTime = GetFrameTime();

		auto needsInitialization = Components | std::views::filter([](const GameObjectComponent* component)
			{
				return !component->IsInitialized;
			});

		for (const auto component : needsInitialization)
		{
			component->OnInitialize();
			component->IsInitialized = true;
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		for (const auto component : Components)
			component->OnUpdate(deltaTime);

		EndDrawing();
	}

	CloseWindow();
}

GameObject* Engine::CreateGameObject()
{
	auto* instance = new GameObject();
	GameObjects.push_back(instance);

	return instance;
}

void Engine::DestroyObjects()
{
	// auto flaggedComponents = Components | std::views::take_while filter([](const GameObjectComponent* component)
	// 	{
	// 		return component->IsFlaggedForDestruction;
	// 	});
	//
	// for (auto component : flaggedComponents)
	// 	component->OnDestroy();

	const auto componentIterator = std::ranges::find_if(Components, [](const GameObjectComponent* component)
		{
			return component->IsFlaggedForDestruction;
		});

	while (componentIterator != Components.end())
	{
		(*componentIterator)->GetOwner()->ComponentsCount--;
		Components.erase(componentIterator);
		delete* componentIterator;
	}

	const auto emptyObject = std::ranges::find_if(GameObjects, [](const GameObject* object)
		{
			return object->ComponentsCount <= 0;
		});

	while (emptyObject != GameObjects.end())
	{


		GameObjects.erase(emptyObject);
		delete* emptyObject;
	}
}

bool Engine::IsValid(GameObject* object) const
{
	if (object == nullptr)
		return false;

	return std::ranges::find(GameObjects, object) != GameObjects.end();
}

bool Engine::IsValid(GameObjectComponent* component) const
{
	if (component == nullptr)
		return false;

	return std::ranges::find(Components, component) != Components.end();
}

void Engine::Destroy(GameObject* object)
{
	auto markedForDestroy = Components | std::views::filter([object](const GameObjectComponent* component)
		{
			return component->GetOwner() == object;
		});

	for (auto component : markedForDestroy)
	{
		component->IsFlaggedForDestruction = true;
	}
}

size_t Engine::GetComponentsCount() const
{
	return Components.size();
}

size_t Engine::GetGameObjectsCount() const
{
	return GameObjects.size();
}
