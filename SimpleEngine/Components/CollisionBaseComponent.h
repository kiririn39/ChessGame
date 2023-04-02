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
    std::map<const CollisionBaseComponent*, unsigned char> collisionsTrackers{};

    bool isValidReference(const CollisionBaseComponent* other) const;

    void PreCollisionsUpdate();
    void UpdateCollisionWith(const CollisionBaseComponent* other);
    void PostCollisionsUpdate();

    friend class EngineCore;

protected:
    virtual void DrawDebugBounds();

public:
    int GetActiveCollisionsCount() const;

    virtual float GetRadius() const;
    virtual bool IsInRadiusWith(const CollisionBaseComponent* other) const;
    virtual bool DoesCollidesWith(const CollisionBaseComponent* other) const;
    virtual void SetDrawDebugBounds(bool doDraw);
};
