#include "CollisionTestComponent.h"

#include "EngineCoreTemplates.h"
#include "GameObjectTemplates.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void CollisionTestComponent::OnCollisionEnter(const CollisionBaseComponent* thisComponent,
                                              const CollisionBaseComponent* otherComponent)
{
    auto ownTransform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (ownTransform == nullptr)
        return;

    auto kingObject = EngineCore::GetInstance()->CreateGameObject("Rook");
    auto rookTransform = kingObject->AddComponentOfType<TransformComponent>();
    rookTransform->SetWorldPosition(ownTransform->GetWorldPosition());
    auto rookSprite = kingObject->AddComponentOfType<SpriteComponent>();
    rookSprite->LoadSpriteFromPath(R"(Resources\B_King.png)");
}

void CollisionTestComponent::OnCollisionUpdate(const CollisionBaseComponent* thisComponent,
                                               const CollisionBaseComponent* otherComponent)
{
}

void CollisionTestComponent::OnCollisionExit(const CollisionBaseComponent* thisComponent,
                                             const CollisionBaseComponent* otherComponent)
{
}
