#pragma once
#include "ChessGameGeneral.h"
#include "Components/GameObjectComponent.h"

class ChessPieceComponent : public GameObjectComponent
{
private:
    ChessPieceType type = ChessPieceType::Pawn;
    ChessPieceColor color = ChessPieceColor::White;

public:
    void InitializePiece(ChessPieceColor Color, ChessPieceType Type);
};
