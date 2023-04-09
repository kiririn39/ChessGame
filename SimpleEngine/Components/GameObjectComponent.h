#pragma once
#include "Object.h"

class GameObject;

class GameObjectComponent : public Object
{
private:
    bool IsInvalid = true;
    bool IsFlaggedForDestruction = false;

    friend class EngineCore;
    friend class MemoryPool;

protected:
    GameObject* OwnerObject = nullptr;
    bool IsInitialized = false;

public:
    bool IsValid();

    virtual ~GameObjectComponent() = default;

    virtual void InitializeInstance(GameObject* owner);
    virtual void OnInitialize();
    virtual void OnUpdate(float deltaTime);
    virtual void OnDestroy();

    void Destroy();
    [[nodiscard]] GameObject* GetOwner() const;
};
