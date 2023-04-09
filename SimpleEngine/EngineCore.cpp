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
    std::ranges::copy(pool.Components | isCollisionComponent | toCollisionComponent,
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
        std::ranges::copy(pool.Components | isNotInitialized, std::back_inserter(needsInitialization));

        for (const auto component : needsInitialization)
        {
            component->IsInitialized = true;
            component->OnInitialize();
        }

        UpdateCollisions();

        auto uiComponents = pool.Components | std::views::filter([](const GameObjectComponent* component)
        {
            return dynamic_cast<const UIComponent*>(component) != nullptr && component->IsInitialized;
        });

        auto standartComponetns = pool.Components | std::views::filter([](const GameObjectComponent* component)
        {
            return dynamic_cast<const UIComponent*>(component) == nullptr && component->IsInitialized;
        });

        Camera2D camera{};

        auto match = std::ranges::find_if(pool.Components, [](const GameObjectComponent* component)
        {
            return dynamic_cast<const Camera2dComponent*>(component) != nullptr;
        });

        if (match != pool.Components.end())
            camera = static_cast<Camera2dComponent*>(*match)->GetCamera();
        else
            Logger::LogWithStackTrace(Level::LOG_WARNING, std::format("Couldn't find any Camera2dComponent\n"));

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        for (const auto component : standartComponetns)
            component->OnUpdate(deltaTime);

        auto renderComponetns = pool.Components | std::views::filter([](GameObjectComponent* component)
        {
            return dynamic_cast<IRenderComponent*>(component) != nullptr && component->IsInitialized;
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

        for (IRenderComponent* component : renderComponetns)
            renderer.AddRenderComponent(component);

        EndDrawing();

        DestroyObjects();
    }

    CloseWindow();
}

GameObject* EngineCore::CreateGameObject()
{
    GameObject* instance = pool.CreateObjectOfType<GameObject>();

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
    auto IsFlaggedComponent = std::views::filter([](const GameObjectComponent* component)
    {
        return component->IsFlaggedForDestruction;
    });

    auto IsEmptyGameobject = std::views::filter([](const GameObject* gameObject)
    {
        return gameObject->ComponentsCount <= 0;
    });

    auto flaggedComponentsView = pool.Components | IsFlaggedComponent;
    std::vector<GameObjectComponent*> flaggedComponents{flaggedComponentsView.begin(), flaggedComponentsView.end()};

    for (GameObjectComponent* component : flaggedComponents)
    {
        component->GetOwner()->ComponentsCount--;
        component->OnDestroy();
    }

    for (auto component : flaggedComponents)
        pool.Invalidate(component);

    auto emptyGameobjectsView = pool.GameObjects | IsEmptyGameobject;
    std::vector<GameObject*> emptyGameobjects{emptyGameobjectsView.begin(), emptyGameobjectsView.end()};

    for (auto gameobject : emptyGameobjects)
        pool.Invalidate(gameobject);
}

bool EngineCore::IsValid(GameObject* object) const
{
    return object != nullptr && !object->IsInvalid();
}

bool EngineCore::IsValid(GameObjectComponent* component)
{
    if (component == nullptr)
        return false;

    return component->IsValid();
}

void EngineCore::Destroy(GameObject* object)
{
    if (!IsValid(object))
        return;

    auto markedForDestroy = pool.Components | std::views::filter([object](const GameObjectComponent* component)
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
    return pool.Components.size();
}

size_t EngineCore::GetGameObjectsCount() const
{
    return pool.GameObjects.size();
}
