#pragma once
#include <cstddef>
#include <array>
#include <vector>
#include <unordered_map>
#include <typeindex>

#include "Components/GameObjectComponent.h"

class MemoryPool
{
private:
    std::array<std::byte, 100000> buffer{};
    std::unordered_map<std::type_index, void*> typesVectors{};

public:
    std::vector<GameObjectComponent*> Components{};
    std::vector<GameObject*> GameObjects{};

    MemoryPool();

    template <typename T> requires std::is_base_of_v<GameObject, T>
    T* CreateObjectOfType();
    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* CreateObjectOfType();

    void Invalidate(GameObjectComponent* instance);
    void Invalidate(GameObject* instance);
};
