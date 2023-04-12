#include "CollisionBaseComponent.h"

#include "GameObjectTemplates.h"
#include "TransformComponent.h"
#include "External/raylib/src/raymath.h"

bool CollisionBaseComponent::isValidReference(CollisionBaseComponent* other)
{
    return other != nullptr && other != this;
}

void CollisionBaseComponent::RecalculateCachedValues()
{
    TransformComponent* thisTransform = GetOwner()->GetComponentOfType<TransformComponent>();

    hasChanged = true;

    Vector3 newPosition = thisTransform->GetWorldPosition();
    Vector3 newRotation = thisTransform->GetWorldRotation();
    Vector3 newScale = thisTransform->GetWorldScale();

    if (collisionRadius == collisionRadius &&
        Vector3Equals(newPosition, cachedPosition) &&
        Vector3Equals(newRotation, cachedRotation) &&
        Vector3Equals(newScale, cachedScale))
        hasChanged = false;

    cachedRadius = collisionRadius;
    cachedPosition = newPosition;
    cachedRotation = newRotation;
    cachedScale = newScale;
}

bool CollisionBaseComponent::HasChangesSinceLastUpdate()
{
    return hasChanged;
}

float CollisionBaseComponent::GetCollisionRadius()
{
    return collisionRadius;
}

void CollisionBaseComponent::DrawDebugBounds()
{
}

int CollisionBaseComponent::GetActiveCollisionsCount()
{
    return activeCollisionCount;
}

bool CollisionBaseComponent::DoesCollidesWith(CollisionBaseComponent* other)
{
    return false;
}

void CollisionBaseComponent::SetDrawDebugBounds(bool doDraw)
{
    doDrawDebugBounds = doDraw;
}
