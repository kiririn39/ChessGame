#pragma once
#include <vector>

#include "Components/CollisionBaseComponent.h"

class CollisionsDetector;

struct CollisionResult
{
    CollisionBaseComponent* FirstComponent;
    CollisionBaseComponent* SecondComponent;

    void (CollisionsDetector::*CollisionAction)(CollisionBaseComponent* leftComponent,
                                                CollisionBaseComponent* rightComponent);
};

class CollisionsDetector
{
private:
    std::vector<CollisionResult> activeCollisions{};

public:
    void UpdateCollisionsFor(std::vector<CollisionBaseComponent*> components);

private:
    void PreUpdateCollisions(std::vector<CollisionBaseComponent*> components);

    auto FindPairInActiveCollisions(CollisionBaseComponent* leftComponent,
                                    CollisionBaseComponent* rightComponent) -> auto;

    std::vector<IReceiveCollisionUpdates*>& GetCollisionReceivers(CollisionBaseComponent* collisionComponent);

    void NotifyOnEnterCollision(CollisionBaseComponent* leftComponent, CollisionBaseComponent* rightComponent);
    void NotifyOnUpdateCollision(CollisionBaseComponent* leftComponent, CollisionBaseComponent* rightComponent);
    void NotifyOnExitCollision(CollisionBaseComponent* leftComponent, CollisionBaseComponent* rightComponent);

    bool IsInRadius(CollisionBaseComponent* leftComponent, CollisionBaseComponent* rightComponent);
};
