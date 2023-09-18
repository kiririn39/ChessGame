#include "CollisionsDetector.h"

#include <optional>

#include "EngineCore.h"
#include "GameObjectTemplates.h"
#include "Components/IReceiveCollisionUpdates.h"
#include "raymath.h"


auto CollisionsDetector::FindPairInActiveCollisions(CollisionBaseComponent* leftComponent,
                                                    CollisionBaseComponent* rightComponent) -> auto
{
    auto FirstPairThatHadCollisionBefore = [leftComponent,rightComponent](
        CollisionResult collisionResult)
    {
        return (collisionResult.FirstComponent == leftComponent || collisionResult.SecondComponent == leftComponent)
            && (collisionResult.FirstComponent == rightComponent || collisionResult.SecondComponent == rightComponent);
    };

    auto iterator = std::ranges::find_if(activeCollisions, FirstPairThatHadCollisionBefore);

    auto result = std::optional(iterator);

    if (iterator != activeCollisions.end())
        return result;

    result.reset();

    return result;
}

void CollisionsDetector::UpdateCollisionsFor(std::vector<CollisionBaseComponent*> components)
{
    PreUpdateCollisions(components);

    for (int i = 0; i < components.size() - 1; i++)
    {
        for (int j = i + 1; j < components.size(); j++)
        {
            CollisionBaseComponent* leftComponent = components.at(i);
            CollisionBaseComponent* rightComponent = components.at(j);

            if (leftComponent == rightComponent)
                continue;

            leftComponent->activeCollisionCount = 0;
            rightComponent->activeCollisionCount = 0;

            auto hadCollisionPreviously = FindPairInActiveCollisions(leftComponent, rightComponent);

            if (!leftComponent->HasChangesSinceLastUpdate() && !rightComponent->HasChangesSinceLastUpdate())
            {
                if (hadCollisionPreviously.has_value())
                {
                    if (hadCollisionPreviously.value()->CollisionAction == &CollisionsDetector::NotifyOnEnterCollision)
                    {
                        hadCollisionPreviously.value()->CollisionAction = &CollisionsDetector::NotifyOnUpdateCollision;
                        NotifyOnUpdateCollision(leftComponent, rightComponent);
                    }
                    else if (hadCollisionPreviously.value()->CollisionAction == &
                        CollisionsDetector::NotifyOnUpdateCollision)
                    {
                        NotifyOnUpdateCollision(leftComponent, rightComponent);
                    }
                    else if (hadCollisionPreviously.value()->CollisionAction == &
                        CollisionsDetector::NotifyOnExitCollision)
                    {
                        activeCollisions.erase(hadCollisionPreviously.value());
                    }
                }
                continue;
            }

            if (!IsInRadius(leftComponent, rightComponent))
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
                    hadCollisionPreviously.value()->CollisionAction = &CollisionsDetector::NotifyOnUpdateCollision;
                    NotifyOnUpdateCollision(leftComponent, rightComponent);

                    continue;
                }

//                activeCollisions.emplace_back(leftComponent, rightComponent,
//                                              &CollisionsDetector::NotifyOnEnterCollision);

                NotifyOnEnterCollision(leftComponent, rightComponent);
                continue;
            }

            if (hadCollisionPreviously.has_value())
            {
                NotifyOnExitCollision(leftComponent, rightComponent);
                activeCollisions.erase(hadCollisionPreviously.value());
            }
        }
    }
}

void CollisionsDetector::PreUpdateCollisions(std::vector<CollisionBaseComponent*> components)
{
    EngineCore* engine = EngineCore::GetInstance();

    auto HasInvalidComponent = [engine, this](CollisionResult collisionResult)
    {
        return !engine->IsValid(collisionResult.FirstComponent) || !engine->IsValid(collisionResult.SecondComponent);
    };

    std::erase_if(activeCollisions, HasInvalidComponent);

    for (auto collision : activeCollisions)
    {
        collision.FirstComponent->activeCollisionCount = 0;
        collision.SecondComponent->activeCollisionCount = 0;
    }

    for (auto component : components)
    {
        component->RecalculateCachedValues();
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
    leftComponent->activeCollisionCount--;
    rightComponent->activeCollisionCount--;

    for (auto collisionReceiver : GetCollisionReceivers(leftComponent))
        collisionReceiver->OnCollisionExit(leftComponent, rightComponent);

    for (auto collisionReceiver : GetCollisionReceivers(rightComponent))
        collisionReceiver->OnCollisionExit(rightComponent, leftComponent);
}

bool CollisionsDetector::IsInRadius(CollisionBaseComponent* leftComponent, CollisionBaseComponent* rightComponent)
{
    float distance = std::abs(Vector3Distance(leftComponent->cachedPosition, rightComponent->cachedPosition));

    return distance - leftComponent->GetCollisionRadius() - rightComponent->GetCollisionRadius() <= 0.0f;
}
