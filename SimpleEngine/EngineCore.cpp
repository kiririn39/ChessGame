#include "EngineCore.h"

#include <algorithm>
#include <ranges>

#include "GameObject.h"
#include "raylib.h"
#include "Components/GameObjectComponent.h"

EngineCore* EngineCore::GetInstance()
{
    if (Instance == nullptr)
        Instance = new EngineCore();

    return Instance;
}

void EngineCore::Run()
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
            component->IsInitialized = true;
            component->OnInitialize();
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        for (const auto component : Components)
            component->OnUpdate(deltaTime);

        EndDrawing();

        DestroyObjects();
    }

    CloseWindow();
}

GameObject* EngineCore::CreateGameObject()
{
    auto* instance = new GameObject();
    GameObjects.push_back(instance);

    return instance;
}

GameObject* EngineCore::CreateGameObject(const std::string& name)
{
    auto instance = CreateGameObject();
    instance->Name = name;

    return instance;
}

void EngineCore::DestroyObjects()
{
    auto flaggedComponents = std::views::filter([](const GameObjectComponent* component)
    {
        return component->IsFlaggedForDestruction;
    });

    for (auto component : Components | flaggedComponents)
    {
        component->GetOwner()->ComponentsCount--;
        component->OnDestroy();
    }

    Components.erase(std::ranges::remove_if(Components, [](const GameObjectComponent* component)
    {
        return component->IsFlaggedForDestruction;
    }).begin(), Components.end());

    GameObjects.erase(std::ranges::remove_if(GameObjects, [](const GameObject* object)
    {
        return object->ComponentsCount <= 0;
    }).begin(), GameObjects.end());
}

bool EngineCore::IsValid(GameObject* object) const
{
    if (object == nullptr)
        return false;

    return std::ranges::find(GameObjects, object) != GameObjects.end();
}

bool EngineCore::IsValid(GameObjectComponent* component) const
{
    if (component == nullptr)
        return false;

    return std::ranges::find(Components, component) != Components.end();
}

void EngineCore::Destroy(GameObject* object)
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

size_t EngineCore::GetComponentsCount() const
{
    return Components.size();
}

size_t EngineCore::GetGameObjectsCount() const
{
    return GameObjects.size();
}
