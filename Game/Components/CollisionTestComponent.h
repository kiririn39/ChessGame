#pragma once
#include "Components/GameObjectComponent.h"
#include "Components/IReceiveCollisionUpdates.h"

class CollisionTestComponent : public GameObjectComponent, public IReceiveCollisionUpdates
{
public:
    void OnCollisionEnter(const CollisionBaseComponent* thisComponent,
                          const CollisionBaseComponent* otherComponent) override;
    void OnCollisionUpdate(const CollisionBaseComponent* thisComponent,
                           const CollisionBaseComponent* otherComponent) override;
    void OnCollisionExit(const CollisionBaseComponent* thisComponent,
                         const CollisionBaseComponent* otherComponent) override;
};
