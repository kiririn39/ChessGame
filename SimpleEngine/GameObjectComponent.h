#pragma once
#include "Object.h"

class GameObject;

class GameObjectComponent : public Object
{
private:
    bool IsInitialized = false;
    bool IsFlaggedForDestruction = false;
    friend class Engine;

protected:
    GameObject* OwnerObject = nullptr;

public:
    virtual ~GameObjectComponent() = default;

    virtual void InitializeInstance(GameObject* owner);
    virtual void OnInitialize();
    virtual void OnUpdate(float deltaTime);
    virtual void OnDestroy();

    void Destroy();
    [[nodiscard]] GameObject* GetOwner() const;
};
