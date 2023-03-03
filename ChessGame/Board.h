#pragma once
#include "Piece.h"

class Board : public GameObject
{
public:
	void OnInitialize();
	void OnUpdate(float deltaTime);
	void OnDestroy();

private:
	Piece* Grid[8][8]{};
	Texture2D texture;
	Vector2 boardPosition_{};
};

