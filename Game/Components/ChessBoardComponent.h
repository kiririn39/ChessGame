#pragma once
#include "BoardTileComponent.h"
#include "Components/GameObjectComponent.h"
#include <raylib.h>


class ChessBoardComponent : public GameObjectComponent
{
private:
    Vector2 piecesPivotPoint{7, 7};
    Vector2 piecesSpacing{16, 16};
    Vector2 tileSize{16, 16};

    static constexpr int TilesInRow = 8;
    static constexpr int TilesInColumn = 8;

    BoardTileComponent* tiles[TilesInRow][TilesInColumn]{};

    void InitializePieces();

public:
    void OnInitialize() override;
};
