#include "CollisionsDetector.h"

#include <optional>

#include "EngineCore.h"
#include "GameObjectTemplates.h"
#include "Components/IReceiveCollisionUpdates.h"


auto CollisionsDetector::FindPairInActiveCollisions(CollisionBaseComponent* leftComponent,
                                                    CollisionBaseComponent* rightComponent) -> auto
{
    bool hadCollisionPreviously = false;
    auto leftKeys = activeCollisions.equal_range(leftComponent);
    auto iterator = leftKeys.first;

    for (; iterator != leftKeys.second; ++iterator)
    {
        if (iterator->second != rightComponent)
            continue;

        hadCollisionPreviously = true;
        break;
    }

    if (!hadCollisionPreviously)
    {
        auto rightKeys = activeCollisions.equal_range(leftComponent);

        for (iterator = rightKeys.first; iterator != rightKeys.second; ++iterator)
        {
            if (iterator->second != leftComponent)
                continue;

            hadCollisionPreviously = true;
            break;
        }
    }

    if (hadCollisionPreviously)
        return std::optional(iterator);

    auto noValue = std::optional(iterator);
    noValue.reset();

    return noValue;
}

void CollisionsDetector::UpdateCollisionsFor(std::vector<CollisionBaseComponent*> components)
{
    EngineCore* engine = EngineCore::GetInstance();

    PreUpdateCollisions();

    for (int i = 0; i < components.size() - 1; i++)
    {
        for (int j = i + 1; j < components.size(); j++)
        {
            CollisionBaseComponent* leftComponent = components.at(i);
            CollisionBaseComponent* rightComponent = components.at(j);

            if (!engine->IsValid(leftComponent) || !engine->IsValid(rightComponent) || leftComponent == rightComponent)
                continue;

            auto hadCollisionPreviously = FindPairInActiveCollisions(leftComponent, rightComponent);

            if (!leftComponent->IsInRadiusWith(rightComponent))
            {
                if (hadCollisionPreviously.has_value())
                {
                    NotifyOnExitCollision(leftComponent, rightComponent);
                    activeCollisions.erase(hadCollisionPreviously.value());
                }

                continue;
            }

            if (leftComponent->DoesCollidesWith(rightComponent))
            {
                if (hadCollisionPreviously.has_value())
                {
                    NotifyOnUpdateCollision(leftComponent, rightComponent);

                    continue;
                }

                activeCollisions.insert({leftComponent, rightComponent});

                NotifyOnEnterCollision(leftComponent, rightComponent);
            }

            if (hadCollisionPreviously.has_value())
            {
                NotifyOnExitCollision(leftComponent, rightComponent);
                activeCollisions.erase(hadCollisionPreviously.value());
            }
        }
    }
}

void CollisionsDetector::PreUpdateCollisions()
{
    EngineCore* engine = EngineCore::GetInstance();

    auto HasInvalidPairs = [engine, this](std::pair<CollisionBaseComponent*, CollisionBaseComponent*> collisionPair)
    {
        return !engine->IsValid(collisionPair.first) && !engine->IsValid(collisionPair.second);
    };

    std::erase_if(activeCollisions, HasInvalidPairs);

    for (auto collision : activeCollisions)
    {
        collision.first->activeCollisionCount = 0;
        collision.second->activeCollisionCount = 0;
    }
}

std::vector<IReceiveCollisionUpdates*>& CollisionsDetector::GetCollisionReceivers(
    CollisionBaseComponent* collisionComponent)
{
    static std::vector<IReceiveCollisionUpdates*> result{};
    result.clear();
    collisionComponent->GetOwner()->GetComponentsOfType<IReceiveCollisionUpdates>(result);

    return result;
}

void CollisionsDetector::NotifyOnEnterCollision(CollisionBaseComponent* leftComponent,
                                                CollisionBaseComponent* rightComponent)
{
    leftComponent->activeCollisionCount++;
    rightComponent->activeCollisionCount++;

    for (auto collisionReceiver : GetCollisionReceivers(leftComponent))
        collisionReceiver->OnCollisionEnter(leftComponent, rightComponent);

    for (auto collisionReceiver : GetCollisionReceivers(rightComponent))
        collisionReceiver->OnCollisionEnter(rightComponent, leftComponent);
}

void CollisionsDetector::NotifyOnUpdateCollision(CollisionBaseComponent* leftComponent,
                                                 CollisionBaseComponent* rightComponent)
{
    leftComponent->activeCollisionCount++;
    rightComponent->activeCollisionCount++;

    for (auto collisionReceiver : GetCollisionReceivers(leftComponent))
        collisionReceiver->OnCollisionUpdate(leftComponent, rightComponent);

    for (auto collisionReceiver : GetCollisionReceivers(rightComponent))
        collisionReceiver->OnCollisionUpdate(rightComponent, leftComponent);
}

void CollisionsDetector::NotifyOnExitCollision(CollisionBaseComponent* leftComponent,
                                               CollisionBaseComponent* rightComponent)
{
    for (auto collisionReceiver : GetCollisionReceivers(leftComponent))
        collisionReceiver->OnCollisionExit(leftComponent, rightComponent);

    for (auto collisionReceiver : GetCollisionReceivers(rightComponent))
        collisionReceiver->OnCollisionExit(rightComponent, leftComponent);
}
