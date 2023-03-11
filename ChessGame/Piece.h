#pragma once
#include "../External/raylib-4.2.0/src/raylib.h"
#include "../SimpleEngine/GameObject.h"

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
