#pragma once
#include <cstddef>
#include <array>
#include <memory_resource>
#include <unordered_map>
#include <typeindex>

#include "Components/GameObjectComponent.h"

class MemoryPool
{
private:
    std::array<std::byte, 100000> buffer{};
    std::pmr::monotonic_buffer_resource memoryResource{buffer.data(), buffer.max_size()};

    std::pmr::unordered_map<std::type_index, void*> typesVectors{&memoryResource};

public:
    std::pmr::vector<GameObjectComponent*> Components{&memoryResource};
    std::pmr::vector<GameObject*> GameObjects{&memoryResource};

    MemoryPool();

    template <typename T> requires std::is_base_of_v<GameObject, T>
    T* CreateObjectOfType();
    template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
    T* CreateObjectOfType();

    void Invalidate(GameObjectComponent* instance);
    void Invalidate(GameObject* instance);
};
