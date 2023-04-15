#include "BoardTileComponent.h"

#include "ChessPieceComponent.h"
#include "GameObjectTemplates.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

Rectangle BoardTileComponent::GetRectangle() const
{
    auto rectangle = RectangleCollisionComponent::GetRectangle();

    rectangle.x += PositionOnBoard.x;
    rectangle.y += PositionOnBoard.y;

    return rectangle;
}

void BoardTileComponent::DrawDebugBounds()
{
    RectangleCollisionComponent::DrawDebugBounds();
}

bool BoardTileComponent::HasPiece() const
{
    return piece == nullptr;
}

void BoardTileComponent::SetPieceInTile(ChessPieceComponent* piece)
{
    this->piece = piece;

    GetOwner()->AddChildGameObject(piece->GetOwner());
    auto pieceTransform = piece->GetOwner()->GetComponentOfType<TransformComponent>();

    Vector3 position;
    position.x = PositionOnBoard.x;
    position.y = PositionOnBoard.y;
    position.z = 0;

    pieceTransform->SetLocalPosition(position);

    auto spriteComponent = piece->GetOwner()->GetComponentOfType<SpriteComponent>();
    spriteComponent->SetRenderOrder(pieceTransform->GetWorldPosition().y);
}

ChessPieceComponent* BoardTileComponent::TakePieceFromTile()
{
    auto result = piece;
    piece = nullptr;

    piece->GetOwner()->Unparent();

    return result;
}
