#pragma once
#include "Object.h"

class GameObject;

class GameObjectComponent : public Object
{
private:
    bool IsFlaggedForDestruction = false;
    friend class EngineCore;

protected:
    GameObject* OwnerObject = nullptr;
    bool IsInitialized = false;

public:
    virtual ~GameObjectComponent() = default;

    virtual void InitializeInstance(GameObject* owner);
    virtual void OnInitialize();
    virtual void OnUpdate(float deltaTime);
    virtual void OnDestroy();

    void Destroy();
    [[nodiscard]] GameObject* GetOwner() const;
};
