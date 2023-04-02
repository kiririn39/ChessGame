#pragma once

class CollisionBaseComponent;

class IReceiveCollisionUpdates
{
public:
    virtual void OnCollisionEnter(const CollisionBaseComponent* thisComponent,
                                  const CollisionBaseComponent* otherComponent) = 0;

    virtual void OnCollisionUpdate(const CollisionBaseComponent* thisComponent,
                                   const CollisionBaseComponent* otherComponent) = 0;

    virtual void OnCollisionExit(const CollisionBaseComponent* thisComponent,
                                 const CollisionBaseComponent* otherComponent) = 0;
};
