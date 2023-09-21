#include "CameraZoomComponent.h"

#include "Logger.h"
#include "Components/Camera2dComponent.h"
#include "Input/Input.h"

void CameraZoomComponent::OnUpdate(float deltaTime)
{
    auto* camera = GetOwner()->GetComponentOfType<Camera2dComponent>();

    if (camera == nullptr)
    {
//        Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
//                                      "CameraZoomComponent can't work, Gameobject: %s has not Camera2dComponent\n",
//                                      OwnerObject->Name));
		assert(false);

        return;
    }

    float zoomSpeed = Input::GetFloatAxisInput(Input::ZoomAxis);

    camera->SetZoom(camera->GetZoom() + (zoomSpeed * deltaTime));
}
