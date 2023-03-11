#pragma once
#include <type_traits>
#include <vector>

class GameObject;
class GameObjectComponent;

class EngineCore
{
public:
    static EngineCore* GetInstance();

    void Run();

    GameObject* CreateGameObject();

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