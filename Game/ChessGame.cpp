#pragma once


#include "GameObjectTemplates.h"
#include "Components/Camera2dComponent.h"
#include "Components/CameraStatsComponent.h"
#include "Components/CameraZoomComponent.h"
#include "Components/ChessBoardComponent.h"
#include "Components/EngineStatsComponent.h"
#include "Components/KeyboardMovementComponent.h"
#include "Components/RectangleCollisionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "raymath.h"
#include "ChessGameGeneral.h"
 
int main()
{
	const auto engine = EngineCore::GetInstance();

	const auto object = engine->CreateGameObject();
	object->AddComponentOfType<EngineStatsComponent>();
	object->AddComponentOfType<TransformComponent>();

	auto boardObject = engine->CreateGameObject("GameBoard");
	boardObject->AddComponentOfType<TransformComponent>();
	auto spriteComponent = boardObject->AddComponentOfType<SpriteComponent>();
	spriteComponent->LoadSpriteFromPath(GetBoardAssetPath());
	boardObject->AddComponentOfType<ChessBoardComponent>();

	auto cameraObject = engine->CreateGameObject("Game Camera");
	auto cameraTransform = cameraObject->AddComponentOfType<TransformComponent>();
	cameraObject->AddComponentOfType<CameraZoomComponent>();
	cameraObject->AddComponentOfType<Camera2dComponent>()->SetZoom(3.0f);
	cameraObject->AddComponentOfType<KeyboardMovementComponent>();
	cameraObject->AddComponentOfType<CameraStatsComponent>();

	boardObject->AddChildGameObject(cameraObject);

	auto rookObject1 = engine->CreateGameObject("Rook");
	auto rookTransform1 = rookObject1->AddComponentOfType<TransformComponent>();
	rookTransform1->SetLocalPosition({ 10, 0, 0 });
	auto rookSprite1 = rookObject1->AddComponentOfType<SpriteComponent>();
	rookSprite1->LoadSpriteFromPath(GetPieceSpriteAssetPath(ChessPieceType::Rook, ChessPieceColor::Black));
	auto rookCollision1 = rookObject1->AddComponentOfType<RectangleCollisionComponent>();
	rookCollision1->SetBounds(rookSprite1->GetSpriteSize());
	rookObject1->AddComponentOfType<KeyboardMovementComponent>();

	auto halfSprite = Vector2Scale(spriteComponent->GetSpriteSize(), 0.5f);
	cameraTransform->SetLocalPosition({ halfSprite.x, halfSprite.y, 0 });

	auto entity = engine->CreateEntity();
	engine->registry.get<TransformComponent>(entity).SetLocalPosition({ -90, -20, 0 });

	SpriteComponent& sprite = engine->registry.emplace<SpriteComponent>(entity);
	sprite.LoadSpriteFromPath(GetPieceSpriteAssetPath(ChessPieceType::Rook, ChessPieceColor::Black));
	engine->Run();
}
