#pragma once

#include "GameObjectComponent.h"
#include "raylib.h"

class IReceiveCollisionUpdates;
class CollisionBaseComponent;

class CollisionBaseComponent : public GameObjectComponent
{
protected:
    bool doDrawDebugBounds = false;
    float collisionRadius = 0.0f;

private:
    unsigned int activeCollisionCount;

    float cachedRadius{};
    Vector3 cachedPosition{};
    Vector3 cachedRotation{};
    Vector3 cachedScale{};
    bool hasChanged = true;

    bool isValidReference(CollisionBaseComponent* other);

    friend class EngineCore;
    friend class CollisionsDetector;

protected:
    virtual void DrawDebugBounds();

public:
    int GetActiveCollisionsCount();
    void RecalculateCachedValues();
    bool HasChangesSinceLastUpdate();
    float GetCollisionRadius();

    virtual bool DoesCollidesWith(CollisionBaseComponent* other);
    virtual void SetDrawDebugBounds(bool doDraw);
};
