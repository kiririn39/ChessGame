#include "RectangleCollisionComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "External/raylib/src/raymath.h"
#include "Input/Input.h"

void RectangleCollisionComponent::DrawDebugBounds()
{
    Rectangle rectangle = GetRectangle();
    Color color = GetActiveCollisionsCount() == 0 ? GREEN : RED;

    DrawRectangleLines(rectangle.x, rectangle.y, rectangle.width, rectangle.height, color);
}

bool RectangleCollisionComponent::DoesCollidesWith( CollisionBaseComponent* other)
{
    const RectangleCollisionComponent* otherBox = dynamic_cast<const RectangleCollisionComponent*>(other);

    if (otherBox == nullptr)
        return false;

    return CheckCollisionRecs(GetRectangle(), otherBox->GetRectangle());
}

void RectangleCollisionComponent::OnUpdate(float deltaTime)
{
    if (IsKeyPressed(Input::DebugKey))
        doDrawDebugBounds = !doDrawDebugBounds;

    if (doDrawDebugBounds)
        DrawDebugBounds();
}

void RectangleCollisionComponent::SetBounds(Vector2 rectangle)
{
    bounds.width = rectangle.x;
    bounds.height = rectangle.y;
    extent = Vector2Scale(rectangle, 0.5f);
    radius = Vector2Length(extent);
}

Rectangle RectangleCollisionComponent::GetRectangle() const
{
    Rectangle result = bounds;
    TransformComponent* transform = GetOwner()->GetComponentOfType<TransformComponent>();

    if (transform != nullptr)
    {
        Vector3 position = transform->GetLocalPosition();

        result.x = position.x;
        result.y = position.y;
    }

    return result;
}

Vector2 RectangleCollisionComponent::GetExtent() const
{
    return extent;
}

float RectangleCollisionComponent::GetRadius()
{
    return radius;
}
