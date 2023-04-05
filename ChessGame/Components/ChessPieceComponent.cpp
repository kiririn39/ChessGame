#include "ChessPieceComponent.h"

#include <format>

#include "GameObjectTemplates.h"
#include "Logger.h"
#include "Components/SpriteComponent.h"
#include "External/raylib/src/raymath.h"

void ChessPieceComponent::InitializePiece(ChessPieceColor Color, ChessPieceType Type)
{
    color = Color;
    type = Type;

    auto spriteComponent = OwnerObject->GetComponentOfType<SpriteComponent>();

    if (spriteComponent == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format("Gameobject: {} ChessPieceComponent"
                                                                  " requires SpriteComponent but could not find one",
                                                                  OwnerObject->Name));
        return;
    }

    spriteComponent->LoadSpriteFromPath(GetPieceSpriteAssetPath(type, color));

    auto spriteSize = spriteComponent->GetSpriteSize();
    auto offset = Vector2Scale(spriteSize, -0.5f);
    offset.x += spriteSize.x / 2.0f;

    spriteComponent->Offset = offset;
}
