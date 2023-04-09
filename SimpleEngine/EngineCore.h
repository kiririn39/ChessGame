#pragma once
#include <raylib.h>
#include <string>
#include <type_traits>
#include <vector>

#include "Renderer.h"
#include "Memory/MemoryPool.h"

class GameObject;
class GameObjectComponent;

class EngineCore
{
private:
    Vector2 windowSize{};
    Renderer renderer{};
    MemoryPool pool{};

    inline static EngineCore* Instance = nullptr;

public:
    static EngineCore* GetInstance();

    Vector2 GetWindowSize() const;

    void Run();

    GameObject* CreateGameObject();
    GameObject* CreateGameObject(const std::string& name);

    template <typename T>
    T* GetComponent(const GameObject* owner) const;

    template <typename T>
    void GetComponents(const GameObject* owner, std::vector<T*>& result) const;

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* AddComponent(GameObject* owner);

    bool IsValid(GameObject* object) const;
    bool IsValid(GameObjectComponent* component);

    void Destroy(GameObject* object);

    [[nodiscard]] size_t GetComponentsCount() const;
    [[nodiscard]] size_t GetGameObjectsCount() const;

private:
    EngineCore() = default;

    void DestroyObjects();

    void UpdateCollisions();
};
