#include "SpriteComponent.h"

#include "GameObjectTemplates.h"
#include "raymath.h"
#include "TransformComponent.h"
#include "Utilities/Format.h"
#include "Logger.h"

void SpriteComponent::FreeAllTextureData()
{
	UnloadTexture(gpuTexture);

	if (cpuTexture.data != nullptr)
		UnloadImage(cpuTexture);
}

void SpriteComponent::FinishTextureLoading()
{
	if (cpuTexture.data == nullptr)
		return;

	gpuTexture = LoadTextureFromImage(cpuTexture);

	UnloadImage(cpuTexture);
	cpuTexture.data = nullptr;
}

void SpriteComponent::LoadSpriteFromPath(const char* path)
{
	if (!FileExists(path))
	{
		Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
			"GameObject: %s SpriteComponent can't work, Can't load a texture from given path as it doesn't exist: %s\n",
			OwnerObject->Name,
			path));
		return;
	}

	FreeAllTextureData();

	cpuTexture = LoadImage(path);

	gpuTexture.width = cpuTexture.width;
	gpuTexture.height = cpuTexture.height;
	gpuTexture.format = cpuTexture.format;
	gpuTexture.mipmaps = cpuTexture.mipmaps;

	if (IsInitialized)
		FinishTextureLoading();
}

Vector2 SpriteComponent::GetSpriteSize() const
{
	return Vector2{ (float)gpuTexture.width, (float)gpuTexture.height };
}

void SpriteComponent::OnInitialize()
{
	FinishTextureLoading();
}

void SpriteComponent::OnDestroy()
{
	FreeAllTextureData();
}

void SpriteComponent::SetRenderOrder(int order)
{
	sortingOrder = order;
}

int SpriteComponent::GetRenderOrder() const
{
	return sortingOrder;
}

void SpriteComponent::Render()
{
	if (gpuTexture.id == 0)
	{
		Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
			"GameObject: %s SpriteComponent can't work, texture id == 0\n",
			OwnerObject->Name));

		return;
	}

	auto* transform = GetOwner()->GetComponentOfType<TransformComponent>();

	if (transform == nullptr)
	{
		Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
			"GameObject: %s SpriteComponent can't work, Gameobject: %s has not TransformComponent\n",
			OwnerObject->Name, OwnerObject->Name));
		return;
	}

	Vector3 scale = transform->GetLocalScale();
	Vector3 localPosition = transform->GetLocalPosition();

	Rectangle originRect = Rectangle{ 0, 0, (float)gpuTexture.width, (float)gpuTexture.height };
	Rectangle destinationRect = originRect;

	destinationRect.width *= scale.x;
	destinationRect.height *= scale.y;
	destinationRect.x = localPosition.x + Offset.x;
	destinationRect.y = localPosition.y + Offset.y;

	DrawTexturePro(gpuTexture, originRect, destinationRect, Vector2Zero(), transform->GetLocalRotation().z, WHITE);
}

void SpriteComponent::Render(TransformComponent* transform)
{
	if (gpuTexture.id == 0)
	{
		Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
			"GameObject: %s SpriteComponent can't work, texture id == 0\n",
			OwnerObject->Name));

		return;
	}

	Vector3 scale = transform->GetLocalScale();
	Vector3 localPosition = transform->GetLocalPosition();

	Rectangle originRect = Rectangle{ 0, 0, (float)gpuTexture.width, (float)gpuTexture.height };
	Rectangle destinationRect = originRect;

	destinationRect.width *= scale.x;
	destinationRect.height *= scale.y;
	destinationRect.x = localPosition.x + Offset.x;
	destinationRect.y = localPosition.y + Offset.y;

	DrawTexturePro(gpuTexture, originRect, destinationRect, Vector2Zero(), transform->GetLocalRotation().z, WHITE);
}
