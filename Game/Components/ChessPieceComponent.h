#pragma once
#include "Components/GameObjectComponent.h"
#include "../ChessGameGeneral.h"

class ChessPieceComponent : public GameObjectComponent
{
private:
    ChessPieceType type = ChessPieceType::Pawn;
    ChessPieceColor color = ChessPieceColor::White;

public:
    void InitializePiece(ChessPieceColor Color, ChessPieceType Type);
};
