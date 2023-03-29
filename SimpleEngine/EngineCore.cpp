#include "EngineCore.h"

#include <algorithm>
#include <format>
#include <ranges>
#include "GameObject.h"
#include "Logger.h"
#include "raylib.h"
#include "Components/Camera2dComponent.h"
#include "Components/GameObjectComponent.h"

EngineCore* EngineCore::GetInstance()
{
    if (Instance == nullptr)
        Instance = new EngineCore();

    return Instance;
}

Vector2 EngineCore::GetWindowSize() const
{
    return windowSize;
}

void EngineCore::Run()
{
    windowSize.x = 1280;
    windowSize.y = 720;

    InitWindow(windowSize.x, windowSize.y, "raylib [core] example - basic window");

    SetTargetFPS(GetMonitorRefreshRate(0));

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

        Camera2D camera{};

        auto match = std::ranges::find_if(Components, [](const GameObjectComponent* component)
        {
            return dynamic_cast<const Camera2dComponent*>(component) != nullptr;
        });

        if (match != Components.end())
            camera = static_cast<Camera2dComponent*>(*match)->GetCamera();
        else
            Logger::LogWithStackTrace(Level::LOG_WARNING, std::format("Couldn't find any Camera2dComponent\n"));

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        for (const auto component : Components)
            component->OnUpdate(deltaTime);

        EndMode2D();
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
