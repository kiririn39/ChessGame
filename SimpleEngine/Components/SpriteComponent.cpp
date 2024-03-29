﻿#include "SpriteComponent.h"

#include "GameObjectTemplates.h"
#include "raymath.h"
#include "TransformComponent.h"
#include "Utilities/Format.h"
#include "Logger.h"

void SpriteComponent::FreeAllTextureData()
{
	UnloadTexture(texture);

	if (preLoadedTextureData.data != nullptr)
		UnloadImage(preLoadedTextureData);
}

void SpriteComponent::FinishTextureLoading()
{
	if (preLoadedTextureData.data == nullptr)
		return;

	texture = LoadTextureFromImage(preLoadedTextureData);

	UnloadImage(preLoadedTextureData);
	preLoadedTextureData.data = nullptr;
}

void SpriteComponent::LoadSpriteFromPath(const char* path)
{
	if (!FileExists(path))
	{
		Logger::LogWithStackTrace(Level::LOG_WARNING, Engine::Format(
				"GameObject: %s SpriteComponent can't work, Can't load a texture from given path as it doesn't exist: %s\n",
				OwnerObject->Name, path));
		return;
	}

	FreeAllTextureData();

	preLoadedTextureData = LoadImage(path);

	texture.width = preLoadedTextureData.width;
	texture.height = preLoadedTextureData.height;
	texture.format = preLoadedTextureData.format;
	texture.mipmaps = preLoadedTextureData.mipmaps;

	if (IsInitialized)
		FinishTextureLoading();
}

Vector2 SpriteComponent::GetSpriteSize() const
{
	return Vector2(texture.width, texture.height);
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
	if (texture.id == 0)
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

	Rectangle originRect = Rectangle{ 0, 0, (float)texture.width, (float)texture.height };
	Rectangle destinationRect = originRect;

	destinationRect.width *= scale.x;
	destinationRect.height *= scale.y;
	destinationRect.x = localPosition.x + Offset.x;
	destinationRect.y = localPosition.y + Offset.y;

	DrawTexturePro(texture, originRect, destinationRect, Vector2Zero(), transform->GetLocalRotation().z, WHITE);
}
