#pragma once
#include <map>

#include "GameObjectComponent.h"

class IReceiveCollisionUpdates;
class CollisionBaseComponent;

class CollisionBaseComponent : public GameObjectComponent
{
protected:
    bool doDrawDebugBounds = false;

private:
    unsigned int activeCollisionCount;
    std::map<CollisionBaseComponent*, unsigned char> collisionsTrackers{};

    bool isValidReference(CollisionBaseComponent* other);

    friend class EngineCore;
    friend class CollisionsDetector;

protected:
    virtual void DrawDebugBounds();

public:
    int GetActiveCollisionsCount();

    virtual float GetRadius();
    virtual bool IsInRadiusWith(CollisionBaseComponent* other);
    virtual bool DoesCollidesWith(CollisionBaseComponent* other);
    virtual void SetDrawDebugBounds(bool doDraw);
};
