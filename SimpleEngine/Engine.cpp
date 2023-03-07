#include "Engine.h"

#include <cassert>
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
    auto flaggedComponents = Components | std::views::filter([](const GameObjectComponent* component)
    {
        return component->IsFlaggedForDestruction;
    });

    for (auto component : flaggedComponents)
        component->OnDestroy();

    const auto deleteIterator = std::ranges::find_if(Components, [](const GameObjectComponent* component)
    {
        return component->IsFlaggedForDestruction;
    });

    while (deleteIterator != Components.end())
    {
        (*deleteIterator)->GetOwner()->ComponentsCount--;
        Components.erase(deleteIterator);
        delete *deleteIterator;
    }

    const auto emptyObjects = std::ranges::find_if(GameObjects, [](const GameObject* object)
    {
        return object->ComponentsCount <= 0;
    });

    while (emptyObjects != GameObjects.end())
    {
        GameObjects.erase(emptyObjects);
        delete *emptyObjects;
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
    IsValid(object);

    auto markedForDestroy = Components | std::views::filter([object](const GameObjectComponent* component)
    {
        return component->GetOwner() == object;
    });

    for (auto component : markedForDestroy)
    {
        component->IsFlaggedForDestruction = true;
    }

    for (auto child : object->Children)
        Destroy(child);
}

size_t Engine::GetComponentsCount() const
{
    return Components.size();
}

size_t Engine::GetGameObjectsCount() const
{
    return GameObjects.size();
}
