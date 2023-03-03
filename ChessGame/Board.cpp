#include "Board.h"

void Board::OnInitialize()
{
	//GameObject::OnInitialize();
	texture = LoadTexture("Resources/board_plain_04.png");
}

void Board::OnUpdate(float deltaTime)
{
	//GameObject::OnUpdate(deltaTime);
	DrawTextureEx(texture, boardPosition_, 0, 2.0f, WHITE);
}

void Board::OnDestroy()
{
	//GameObject::OnDestroy();
	UnloadTexture(texture);
}
