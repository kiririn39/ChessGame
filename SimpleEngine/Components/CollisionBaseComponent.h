#pragma once
#include <map>
#include <vector>

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

    void PreCollisionsUpdate();
    void UpdateCollisionWith(CollisionBaseComponent* other);
    void PostCollisionsUpdate();

    friend class EngineCore;

protected:
    virtual void DrawDebugBounds();

public:
    int GetActiveCollisionsCount();

    virtual float GetRadius();
    virtual bool IsInRadiusWith(CollisionBaseComponent* other);
    virtual bool DoesCollidesWith(CollisionBaseComponent* other);
    virtual void SetDrawDebugBounds(bool doDraw);
};
