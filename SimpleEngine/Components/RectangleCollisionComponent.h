#pragma once
#include "CollisionBaseComponent.h"
#include "External/raylib/src/raylib.h"

class RectangleCollisionComponent : public CollisionBaseComponent
{
private:
    Rectangle bounds{};
    Vector2 extent{};
    float radius = 0.0f;

protected:
    void DrawDebugBounds() override;

public:
    void SetBounds(Vector2 rectangle);
    virtual Rectangle GetRectangle() const;
    Vector2 GetExtent() const;

    float GetRadius() const override;

    bool DoesCollidesWith(const CollisionBaseComponent* other) const override;
    void OnUpdate(float deltaTime) override;
};
