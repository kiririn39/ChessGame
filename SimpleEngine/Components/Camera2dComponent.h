#pragma once

#include "GameObjectTemplates.h"

class Camera2dComponent : public GameObjectComponent
{
private:
	Vector2 cameraOffset{};
	float zoom = 1.0f;

public:
	void OnInitialize() override;

	Camera2D GetCamera();

	void SetZoom(float zoom);

	float GetZoom() const;
};
