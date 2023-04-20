#pragma once

#include <raylib-cpp.hpp>

#include "GameObjectTemplates.h"

class Camera2dComponent : public GameObjectComponent
{
private:
	raylib::Vector2 cameraOffset{};
	float zoom = 1.0f;

public:
	void OnInitialize() override;

	raylib::Camera2D GetCamera();

	void SetZoom(float zoom);

	float GetZoom() const;
};
