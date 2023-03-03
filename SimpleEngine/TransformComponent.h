#pragma once
#include <raylib.h>

#include "GameObjectComponent.h"

class TransformComponent : public GameObjectComponent
{
private:
	Vector3 LocalPosition = {};
	Vector3 LocalRotation = {};
	Vector3 LocalScale = {};

public:
	Vector3 GetLocalPosition();
	Vector3 GetWorldPosition();

	Vector3 GetLocalRotation();
	Vector3 GetWorldRotation();

	Vector3 GetLocalScale();
	Vector3 GetWorldScale();

	Vector3 SetLocalPosition();
	Vector3 SetWorldPosition();

	Vector3 SetLocalRotation();
	Vector3 SetWorldRotation();

	Vector3 SetLocalScale();
	Vector3 SetWorldScale();
};