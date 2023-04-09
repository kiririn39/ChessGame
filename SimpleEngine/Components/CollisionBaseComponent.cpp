#include "CollisionBaseComponent.h"

#include <format>
#include <ranges>

#include "EngineCore.h"
#include "GameObjectTemplates.h"
#include "Logger.h"
#include "TransformComponent.h"
#include <raymath.h>

#include "IReceiveCollisionUpdates.h"

bool CollisionBaseComponent::isValidReference(CollisionBaseComponent* other)
{
    return other != nullptr && other != this;
}

void CollisionBaseComponent::PreCollisionsUpdate()
{
    EngineCore* engine = EngineCore::GetInstance();

    auto IsDeletedComponent = [engine, this](std::pair<CollisionBaseComponent*, unsigned char> tracker)
    {
        return !isValidReference(tracker.first) || !engine->IsValid(tracker.first);
    };

    std::erase_if(collisionsTrackers, IsDeletedComponent);

    for (auto& HitsCount : collisionsTrackers | std::views::values)
        HitsCount = 0;
}

void CollisionBaseComponent::UpdateCollisionWith(CollisionBaseComponent* other)
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
