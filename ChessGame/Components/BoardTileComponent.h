#pragma once
#include "Components/RectangleCollisionComponent.h"

class ChessPieceComponent;

class BoardTileComponent : public RectangleCollisionComponent
{
private:
    ChessPieceComponent* piece = nullptr;

public:
    Vector2 PositionOnBoard;

    Rectangle GetRectangle() const override;
    void DrawDebugBounds() override;

    bool HasPiece() const;
    void SetPieceInTile(ChessPieceComponent* piece);
    ChessPieceComponent* TakePieceFromTile();
};
