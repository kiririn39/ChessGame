#include "ChessBoardComponent.h"

#include "GameObjectTemplates.h"
#include "ChessPieceComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void ChessBoardComponent::InitializePieces()
{
    auto GeneratePiece = [](ChessPieceType type, ChessPieceColor color)
    {
        GameObject* pieceObject = EngineCore::GetInstance()->CreateGameObject();

        ChessPieceComponent* pieceComponent = pieceObject->AddComponentOfType<ChessPieceComponent>();
        pieceObject->AddComponentOfType<SpriteComponent>();
        pieceObject->AddComponentOfType<TransformComponent>();
        pieceComponent->InitializePiece(color, type);

        return pieceComponent;
    };

    auto GenerateTeam = [&](ChessPieceColor color)
    {
        int frontRow = color == ChessPieceColor::White ? 6 : 1;
        int backRow = color == ChessPieceColor::White ? 7 : 0;

        tiles[0][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Rook, color));
        tiles[1][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Knight, color));
        tiles[2][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Bishop, color));
        tiles[3][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Queen, color));
        tiles[4][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::King, color));
        tiles[5][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Bishop, color));
        tiles[6][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Knight, color));
        tiles[7][backRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Rook, color));

        for (int i = 0; i < 8; i++)
            tiles[i][frontRow]->SetPieceInTile(GeneratePiece(ChessPieceType::Pawn, color));
    };

    GenerateTeam(ChessPieceColor::White);
    GenerateTeam(ChessPieceColor::Black);
}

void ChessBoardComponent::OnInitialize()
{
    for (int y = 0; y < TilesInColumn; ++y)
    {
        for (int x = 0; x < TilesInRow; ++x)
        {
            auto position = piecesPivotPoint;
            position.x += x * piecesSpacing.x;
            position.y += y * piecesSpacing.y;

            auto* tile = OwnerObject->AddComponentOfType<BoardTileComponent>();
            tile->PositionOnBoard = position;
            tile->SetBounds(tileSize);

            tiles[x][y] = tile;
        }
    }

    InitializePieces();
}
