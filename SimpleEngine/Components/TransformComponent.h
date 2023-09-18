#pragma once

#include "GameObjectComponent.h"
#include "raylib.h"

class TransformComponent : public GameObjectComponent
{
 private:
	bool doDrawDebugPoint = false;
	Vector3 LocalPosition = { 0, 0, 0 };
	Vector3 LocalRotation = { 0, 0, 0 };
	Vector3 LocalScale = { 1, 1, 1 };

	Vector3 ComputeLocalValue(Vector3 (TransformComponent::* parentWorldValueGetter)() const,
		Vector3 localValue) const;

 public:
	void OnUpdate(float deltaTime) override;

	Vector3 GetLocalPosition() const;
	Vector3 GetWorldPosition() const;

	Vector3 GetLocalRotation() const;
	Vector3 GetWorldRotation() const;

	Vector3 GetLocalScale() const;
	Vector3 GetWorldScale() const;

	Vector3 SetLocalPosition(Vector3 value);
	Vector3 SetWorldPosition(Vector3 value);

	Vector3 SetLocalRotation(Vector3 value);
	Vector3 SetWorldRotation(Vector3 value);

	Vector3 SetLocalScale(Vector3 value);
	Vector3 SetWorldScale(Vector3 value);
};
