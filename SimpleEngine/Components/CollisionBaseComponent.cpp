#include "CollisionBaseComponent.h"

#include <format>
#include <ranges>

#include "EngineCore.h"
#include "GameObjectTemplates.h"
#include "Logger.h"
#include "TransformComponent.h"
#include <raymath.h>

#include "IReceiveCollisionUpdates.h"

bool CollisionBaseComponent::isValidReference(const CollisionBaseComponent* other) const
{
    return other != nullptr && other != this;
}

void CollisionBaseComponent::PreCollisionsUpdate()
{
    EngineCore* engine = EngineCore::GetInstance();

    auto isDeletedComponent = [engine, this](std::pair<const CollisionBaseComponent*, unsigned char> tracker)
    {
        return !isValidReference(tracker.first) || !engine->IsValid(tracker.first);
    };

    std::erase_if(collisionsTrackers, isDeletedComponent);

    for (auto& HitsCount : collisionsTrackers | std::views::values)
        HitsCount = 0;
}

void CollisionBaseComponent::UpdateCollisionWith(const CollisionBaseComponent* other)
{
    if (!isValidReference(other) || !IsInRadiusWith(other) || !DoesCollidesWith(other))
        return;

    auto iterator = collisionsTrackers.find(other);

    if (iterator != collisionsTrackers.end())
        iterator->second += 2;
    else
    {
        auto [it, inserted] = collisionsTrackers.emplace(other, 1);
        iterator = it;
    }

    if (iterator->second > 2)
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format(
                                      "GameObject: {} CollisionBaseComponent with Gameobject: {} CollisionBaseComponent 2 or more times",
                                      OwnerObject->Name, other->OwnerObject->Name));
}

void CollisionBaseComponent::PostCollisionsUpdate()
{
    activeCollisionCount = 0;
    std::vector<IReceiveCollisionUpdates*> collisionUpdateReceivers{};

    OwnerObject->GetComponentsOfType<IReceiveCollisionUpdates>(collisionUpdateReceivers);

    auto hasStoppedCollidingWith = [](std::pair<const CollisionBaseComponent*, unsigned char> tracker)
    {
        return tracker.second == 0;
    };

    for (auto& [otherComponent, collisionCount] : collisionsTrackers)
    {
        if (collisionCount == 0)
        {
            for (IReceiveCollisionUpdates* collisionUpdateReceiver : collisionUpdateReceivers)
                collisionUpdateReceiver->OnCollisionExit(this, otherComponent);
            continue;
        }

        if (collisionCount == 1)
            for (IReceiveCollisionUpdates* collisionUpdateReceiver : collisionUpdateReceivers)
                collisionUpdateReceiver->OnCollisionEnter(this, otherComponent);

        if (collisionCount == 2)
            for (IReceiveCollisionUpdates* collisionUpdateReceiver : collisionUpdateReceivers)
                collisionUpdateReceiver->OnCollisionUpdate(this, otherComponent);

        activeCollisionCount++;
    }

    std::erase_if(collisionsTrackers, hasStoppedCollidingWith);
}

void CollisionBaseComponent::DrawDebugBounds()
{
}

int CollisionBaseComponent::GetActiveCollisionsCount() const
{
    return activeCollisionCount;
}

float CollisionBaseComponent::GetRadius() const
{
    return 0.0f;
}

bool CollisionBaseComponent::IsInRadiusWith(const CollisionBaseComponent* other) const
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

bool CollisionBaseComponent::DoesCollidesWith(const CollisionBaseComponent* other) const
{
    return false;
}

void CollisionBaseComponent::SetDrawDebugBounds(bool doDraw)
{
    doDrawDebugBounds = doDraw;
}
