﻿#include "Camera2dComponent.h"

//#include <boost/format.hpp>
#include "Logger.h"
#include "TransformComponent.h"
#include "raymath.hpp"

void Camera2dComponent::OnInitialize()
{
	const auto windowSize = EngineCore::GetInstance()->GetWindowSize();

	cameraOffset = Vector2Scale(windowSize, 0.5f);
}

raylib::Camera2D Camera2dComponent::GetCamera()
{
	auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

	if (transform == nullptr)
	{
//		std::string
//				message = (boost::format(
//				"GameObject: %s Camera2dComponent can't work, Gameobject: %s has not TransformComponent\n")
//						   % OwnerObject->Name % OwnerObject->Name).str();

		//Logger::LogWithStackTrace(Level::LOG_WARNING, message);

		return raylib::Camera2D();
	}

	const auto localPosition = transform->GetLocalPosition();

	raylib::Camera2D camera;
	camera.offset = cameraOffset;
	camera.zoom = zoom;
	camera.rotation = transform->GetLocalRotation().z;
	camera.target.x = localPosition.x;
	camera.target.y = localPosition.y;

	return camera;
}

void Camera2dComponent::SetZoom(float zoom)
{
	this->zoom = zoom;
}

float Camera2dComponent::GetZoom() const
{
	return zoom;
}
