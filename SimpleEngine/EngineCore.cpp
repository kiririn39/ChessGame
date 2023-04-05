#include "EngineCore.h"

#include <algorithm>
#include <format>
#include <ranges>
#include "GameObject.h"
#include "Logger.h"
#include "raylib.h"
#include "Components/Camera2dComponent.h"
#include "Components/CollisionBaseComponent.h"
#include "Components/GameObjectComponent.h"
#include "Components/UIComponent.h"

void EngineCore::UpdateCollisions()
{
    auto isCollisionComponent = std::views::filter([](GameObjectComponent* component)
    {
        return dynamic_cast<CollisionBaseComponent*>(component) != nullptr;
    });
    auto toCollisionComponent = std::views::transform(
        [](GameObjectComponent* component) -> CollisionBaseComponent*
        {
            return dynamic_cast<CollisionBaseComponent*>(component);
        });

    static std::vector<CollisionBaseComponent*> collisionComponents;
    collisionComponents.clear();
    std::ranges::copy(Components | isCollisionComponent | toCollisionComponent,
                      std::back_inserter(collisionComponents));

    for (CollisionBaseComponent* collisionComponent : collisionComponents)
        collisionComponent->PreCollisionsUpdate();

    for (CollisionBaseComponent* collisionComponent : collisionComponents)
        for (CollisionBaseComponent* otherComponent : collisionComponents)
            collisionComponent->UpdateCollisionWith(otherComponent);

    for (CollisionBaseComponent* collisionComponent : collisionComponents)
        collisionComponent->PostCollisionsUpdate();
}

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
    windowSize.x = 1280 * 2;
    windowSize.y = 720 * 2;

    InitWindow(windowSize.x, windowSize.y, "raylib [core] example - basic window");

    SetTargetFPS(GetMonitorRefreshRate(0));

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        auto isNotInitialized = std::views::filter([](const GameObjectComponent* component)
        {
            return !component->IsInitialized;
        });

        static std::vector<GameObjectComponent*> needsInitialization;
        needsInitialization.clear();
        std::ranges::copy(Components | isNotInitialized, std::back_inserter(needsInitialization));

        for (const auto component : needsInitialization)
        {
            component->IsInitialized = true;
            component->OnInitialize();
        }

        UpdateCollisions();

        auto uiComponents = Components | std::views::filter([](const GameObjectComponent* component)
        {
            return dynamic_cast<const UIComponent*>(component) != nullptr && component->IsInitialized;
        });

        auto standartComponetns = Components | std::views::filter([](const GameObjectComponent* component)
        {
            return dynamic_cast<const UIComponent*>(component) == nullptr && component->IsInitialized;
        });

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

        for (const auto component : standartComponetns)
            component->OnUpdate(deltaTime);

        auto renderComponetns = Components | std::views::filter([](GameObjectComponent* component)
        {
            auto b1 =  dynamic_cast<IRenderComponent*>(component) != nullptr && component->IsInitialized;
            return b1;
        }) | std::views::transform([](GameObjectComponent* component)
        {
            return dynamic_cast<IRenderComponent*>(component);
        });

        for (IRenderComponent* component : renderComponetns)
            renderer.AddRenderComponent(component);

        renderer.Render();
        EndMode2D();
                
        for (const auto component : uiComponents)
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
        if (auto* renderComponent = dynamic_cast<IRenderComponent*>(component))
            renderer.RemoveRenderComponent(renderComponent);

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

bool EngineCore::IsValid(const GameObject* object) const
{
    if (object == nullptr)
        return false;

    const auto obj = const_cast<GameObject*>(object);

    return std::ranges::find(GameObjects, obj) != GameObjects.end();
}

bool EngineCore::IsValid(const GameObjectComponent* component) const
{
    if (component == nullptr)
        return false;

    const auto comp = const_cast<GameObjectComponent*>(component);

    return std::ranges::find(Components, comp) != Components.end();
}

void EngineCore::Destroy(GameObject* object)
{
    IsValid(object);

    auto markedForDestroy = Components | std::views::filter([object](const GameObjectComponent* component)
    {
        return component->GetOwner() == object;
    });

    for (auto component : markedForDestroy)
        component->Destroy();

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
