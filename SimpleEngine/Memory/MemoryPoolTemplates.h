#pragma once
#include <assert.h>

#include "MemoryPool.h"

template <typename T> requires std::is_base_of_v<GameObject, T>
T* MemoryPool::CreateObjectOfType()
{
    std::type_index componentType = std::type_index(typeid(T));
    auto iterator = typesVectors.find(componentType);
    T* result;

    if (iterator == typesVectors.end())
    {
        void* memoryForContainer = memoryResource.allocate(sizeof(std::pmr::vector<T>));
        std::pmr::vector<T>* container = new(memoryForContainer) std::pmr::vector<T>{&memoryResource};

        container->reserve(100);
        result = &container->emplace_back();
        GameObjects.push_back(result);
        typesVectors.insert_or_assign(componentType, container);

        result->isInvalid = false;

        return result;
    }

    std::pmr::vector<T>* container = static_cast<std::pmr::vector<T>*>(iterator->second);
    auto FirstReusableInstance = [](T& instance) { return instance.isInvalid; };

    auto FirstReusableComponent = std::find_if(container->begin(), container->end(), FirstReusableInstance);

    if (FirstReusableComponent != container->end())
    {
        result = &*FirstReusableComponent;

        result->isInvalid = false;
        GameObjects.push_back(result);

        return result;
    }

    int placesLeft = container->capacity() - container->size();

    if (placesLeft <= 0)
        assert(false);

    result = &container->emplace_back();
    result->isInvalid = false;
    GameObjects.push_back(result);

    return result;
}

template <typename T> requires std::is_base_of_v<GameObjectComponent, T>
T* MemoryPool::CreateObjectOfType()
{
    std::type_index componentType = std::type_index(typeid(T));
    auto iterator = typesVectors.find(componentType);
    T* result;

    if (iterator == typesVectors.end())
    {
        void* memoryForContainer = memoryResource.allocate(sizeof(std::pmr::vector<T>));
        std::pmr::vector<T>* container = new(memoryForContainer) std::pmr::vector<T>{&memoryResource};

        container->reserve(100);
        result = &container->emplace_back();
        Components.push_back(result);
        typesVectors.insert_or_assign(componentType, container);

        result->IsInvalid = false;

        return result;
    }

    std::pmr::vector<T>* container = static_cast<std::pmr::vector<T>*>(iterator->second);
    auto FirstReusableInstance = [](T& instance) { return !instance.IsValid(); };

    auto FirstReusableComponent = std::find_if(container->begin(), container->end(), FirstReusableInstance);

    if (FirstReusableComponent != container->end())
    {
        result = &*FirstReusableComponent;

        result->IsInvalid = false;
        Components.push_back(result);

        return result;
    }

    int placesLeft = container->capacity() - container->size();

    if (placesLeft <= 0)
        assert(false);

    result = &container->emplace_back();
    result->IsInvalid = false;
    Components.push_back(result);

    return result;
}
