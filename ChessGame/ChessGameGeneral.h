#pragma once
#include <assert.h>
#include <string>

enum class ChessPieceType
{
    Bishop,
    King,
    Knight,
    Pawn,
    Queen,
    Rook,
};

enum class ChessPieceColor
{
    White,
    Black
};

inline const char* GetPieceSpriteAssetPath(ChessPieceType type, ChessPieceColor team)
{
    if (type == ChessPieceType::Bishop && team == ChessPieceColor::White)
        return R"(Resources\W_Bishop.png)";
    if (type == ChessPieceType::Bishop && team == ChessPieceColor::Black)
        return R"(Resources\B_Bishop.png)";

    if (type == ChessPieceType::King && team == ChessPieceColor::White)
        return R"(Resources\W_King.png)";
    if (type == ChessPieceType::King && team == ChessPieceColor::Black)
        return R"(Resources\B_King.png)";

    if (type == ChessPieceType::Knight && team == ChessPieceColor::White)
        return R"(Resources\W_Knight.png)";
    if (type == ChessPieceType::Knight && team == ChessPieceColor::Black)
        return R"(Resources\B_Knight.png)";

    if (type == ChessPieceType::Pawn && team == ChessPieceColor::White)
        return R"(Resources\W_Pawn.png)";
    if (type == ChessPieceType::Pawn && team == ChessPieceColor::Black)
        return R"(Resources\B_Pawn.png)";

    if (type == ChessPieceType::Queen && team == ChessPieceColor::White)
        return R"(Resources\W_Queen.png)";
    if (type == ChessPieceType::Queen && team == ChessPieceColor::Black)
        return R"(Resources\B_Queen.png)";

    if (type == ChessPieceType::Rook && team == ChessPieceColor::White)
        return R"(Resources\W_Rook.png)";
    if (type == ChessPieceType::Rook && team == ChessPieceColor::Black)
        return R"(Resources\B_Rook.png)";

    assert(false, "Unsupported color/piece type combination");
}
