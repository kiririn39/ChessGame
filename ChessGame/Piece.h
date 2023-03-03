#pragma once
#include <raylib.h>
#include "GameObject.h"

class Piece : public GameObject
{
public:
	~Piece() override = default;

	void OnInitialize() ;
	void OnUpdate(float deltaTime) ;
	void OnDestroy() ;

protected:
	Texture2D texture;
	Vector2 boardPosition_{};
};