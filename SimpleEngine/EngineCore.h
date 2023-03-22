#pragma once
#include <raylib.h>
#include <string>
#include <type_traits>
#include <vector>

class GameObject;
class GameObjectComponent;

class EngineCore
{
private:
    Vector2 windowSize{};

public:
    static EngineCore* GetInstance();

    Vector2 GetWindowSize() const;

    void Run();

    GameObject* CreateGameObject();
    GameObject* CreateGameObject(const std::string& name);

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* GetComponent(GameObject* owner);

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* AddComponent(GameObject* owner);

    bool IsValid(GameObject* object) const;
    bool IsValid(GameObjectComponent* component) const;

    void Destroy(GameObject* object);

    [[nodiscard]] size_t GetComponentsCount() const;
    [[nodiscard]] size_t GetGameObjectsCount() const;

private:
    inline static EngineCore* Instance = nullptr;
    std::vector<GameObject*> GameObjects{};
    std::vector<GameObjectComponent*> Components{};

    EngineCore() = default;
    void DestroyObjects();
};
