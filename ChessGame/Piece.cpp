#include "Piece.h"

void Piece::OnInitialize()
{
	//GameObject::OnInitialize();
	texture = LoadTexture("Resources/B_Bishop.png");
}

void Piece::OnUpdate(float deltaTime)
{
	//GameObject::OnUpdate(deltaTime);
	DrawTexture(texture, boardPosition_.x, boardPosition_.y, WHITE);
}

void Piece::OnDestroy()
{
	//GameObject::OnDestroy();
	UnloadTexture(texture);
}
