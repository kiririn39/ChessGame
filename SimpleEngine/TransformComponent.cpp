#include "TransformComponent.h"

#include "GameObject.h"
#include "raymath.h"


Vector3 TransformComponent::ComputeLocalValue(Vector3 (TransformComponent::* parentWorldValueGetter)() const,
                                              Vector3 localValue) const
{
    const auto parent = OwnerObject->GetParent();

    if (parent == nullptr)
        return localValue;

    const auto parentTransform = parent->GetComponentOfType<TransformComponent>();

    if (parentTransform == nullptr)
        return localValue;

    return Vector3Add((parentTransform->*parentWorldValueGetter)(), localValue);
}

Vector3 TransformComponent::GetLocalPosition() const
{
    return LocalPosition;
}

Vector3 TransformComponent::GetWorldPosition() const
{
    return ComputeLocalValue(&TransformComponent::GetWorldPosition, GetLocalPosition());
}

Vector3 TransformComponent::GetLocalRotation() const
{
    return LocalRotation;
}

Vector3 TransformComponent::GetWorldRotation() const
{
    const auto localRotation = GetLocalRotation();

    const auto parent = OwnerObject->GetParent();

    if (parent == nullptr)
        return localRotation;

    const auto parentTransform = parent->GetComponentOfType<TransformComponent>();

    if (parentTransform == nullptr)
        return localRotation;

    const auto localQuaternion = QuaternionFromEuler(LocalRotation.x, LocalRotation.y, LocalRotation.z);
    const auto parentRotation = parentTransform->GetWorldRotation();
    const auto parentQuaternion = QuaternionFromEuler(parentRotation.x, parentRotation.y, parentRotation.z);

    return QuaternionToEuler(QuaternionAdd(parentQuaternion, localQuaternion));
}

Vector3 TransformComponent::GetLocalScale() const
{
    return LocalScale;
}

Vector3 TransformComponent::GetWorldScale() const
{
    return ComputeLocalValue(&TransformComponent::GetWorldScale, GetLocalScale());
}

Vector3 TransformComponent::SetLocalPosition(Vector3 value)
{
    LocalPosition = value;
    return LocalPosition;
}

Vector3 TransformComponent::SetWorldPosition(Vector3 value)
{
    const auto distance = Vector3Subtract(value, GetWorldPosition());
    SetLocalPosition(Vector3Add(LocalPosition, distance));

    return GetWorldPosition();
}

Vector3 TransformComponent::SetLocalRotation(Vector3 value)
{
    LocalRotation = value;
    return LocalRotation;
}

Vector3 TransformComponent::SetWorldRotation(Vector3 value)
{
    const Vector3 worldRotation = GetWorldRotation();
    const Quaternion valueQuaternion = QuaternionFromEuler(value.x, value.y, value.z);
    const Quaternion worldQuaternion = QuaternionFromEuler(worldRotation.x, worldRotation.y, worldRotation.z);

    const auto distance = QuaternionSubtract(valueQuaternion, worldQuaternion);

    SetLocalRotation(QuaternionToEuler(QuaternionAdd(worldQuaternion, distance)));

    return GetWorldRotation();
}

Vector3 TransformComponent::SetLocalScale(Vector3 value)
{
    LocalScale = value;
    return LocalScale;
}

Vector3 TransformComponent::SetWorldScale(Vector3 value)
{
    const auto delta = Vector3Subtract(value, GetWorldScale());

    return SetLocalScale(Vector3Add(LocalScale, delta));
}
