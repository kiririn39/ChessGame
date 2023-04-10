#include "CollisionBaseComponent.h"

#include "GameObjectTemplates.h"
#include "TransformComponent.h"
#include <raymath.h>

bool CollisionBaseComponent::isValidReference(CollisionBaseComponent* other)
{
    return other != nullptr && other != this;
}

void CollisionBaseComponent::DrawDebugBounds()
{
}

int CollisionBaseComponent::GetActiveCollisionsCount()
{
    return activeCollisionCount;
}

float CollisionBaseComponent::GetRadius()
{
    return 0.0f;
}

bool CollisionBaseComponent::IsInRadiusWith(CollisionBaseComponent* other)
{
    if (!isValidReference(other))
        return false;

    TransformComponent* otherTransform = other->GetOwner()->GetComponentOfType<TransformComponent>();
    TransformComponent* thisTransform = other->GetOwner()->GetComponentOfType<TransformComponent>();

    if (otherTransform == nullptr || thisTransform == nullptr)
        return false;

    Vector3 otherPosition = otherTransform->GetLocalPosition();
    Vector3 thisPosition = thisTransform->GetLocalPosition();

    float distance = Vector3Distance(otherPosition, thisPosition);

    return distance - GetRadius() - other->GetRadius() <= 0.0f;
}

bool CollisionBaseComponent::DoesCollidesWith(CollisionBaseComponent* other)
{
    return false;
}

void CollisionBaseComponent::SetDrawDebugBounds(bool doDraw)
{
    doDrawDebugBounds = doDraw;
}
