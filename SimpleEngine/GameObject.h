#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>

#include "Object.h"
class GameObjectComponent;
class EngineCore;

class GameObject : public Object
{
private:
    uint16_t ComponentsCount{};

    GameObject* Parent = nullptr;
    std::vector<GameObject*> Children{};

    friend class EngineCore;

public:
    virtual ~GameObject() = default;

    void Destroy();

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* GetComponentOfType();

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    void AddComponentOfType();

    void AddChildGameObject(GameObject* object);
    void RemoveChildGameObject(GameObject* object);
    [[nodiscard]] GameObject* GetChildGameObject(uint16_t index) const;
    [[nodiscard]] size_t GetChildrenCount() const;
    [[nodiscard]] GameObject* GetParent() const;
    [[nodiscard]] auto GetChildren() const;
};