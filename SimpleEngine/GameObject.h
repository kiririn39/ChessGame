#pragma once
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#include "Object.h"
class GameObjectComponent;
class EngineCore;

class GameObject : public Object
{
private:
    bool isInvalid;
    uint16_t ComponentsCount{};

    GameObject* Parent = nullptr;
    std::vector<GameObject*> Children{};

    friend class EngineCore;
    friend class MemoryPool;

public:
    std::string Name;

public:
    bool IsInvalid();

    virtual ~GameObject() = default;

    void Destroy();

    template <typename T>
    T* GetComponentOfType() const;

    template <typename T>
    void GetComponentsOfType(std::vector<T*>& result) const;

    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* AddComponentOfType();

    void AddChildGameObject(GameObject* object);
    void RemoveChildGameObject(GameObject* object);
    void Unparent();
    [[nodiscard]] GameObject* GetChildGameObject(uint16_t index) const;
    [[nodiscard]] size_t GetChildrenCount() const;
    [[nodiscard]] GameObject* GetParent() const;
    [[nodiscard]] auto GetChildren() const;
};
