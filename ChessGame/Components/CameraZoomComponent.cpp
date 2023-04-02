#include "CameraZoomComponent.h"

#include <format>

#include "Logger.h"
#include "Components/Camera2dComponent.h"
#include "Input/Input.h"

void CameraZoomComponent::OnUpdate(float deltaTime)
{
    auto* camera = GetOwner()->GetComponentOfType<Camera2dComponent>();

    if (camera == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING, std::format(
                                      "CameraZoomComponent can't work, Gameobject: {} has not Camera2dComponent\n",
                                      OwnerObject->Name));
        return;
    }

    float zoomSpeed = Input::GetFloatAxisInput(Input::ZoomAxis);

    camera->SetZoom(camera->GetZoom() + (zoomSpeed * deltaTime));
}
