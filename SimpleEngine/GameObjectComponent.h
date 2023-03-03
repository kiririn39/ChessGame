#pragma once

class GameObject;

class GameObjectComponent
{
private:
	GameObject* OwnerObject = nullptr;
	bool IsInitialized = false;
	bool IsFlaggedForDestruction = false;
	friend class Engine;

public:
	virtual ~GameObjectComponent() = default;

	virtual void InitializeInstance(GameObject* owner);
	virtual void OnInitialize();
	virtual void OnUpdate(float deltaTime);
	virtual void OnDestroy();

	[[nodiscard]] GameObject* GetOwner() const;
};
