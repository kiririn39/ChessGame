#include "GameObject.h"
#include "Engine.h"

void GameObject::Destroy()
{
	Engine::GetInstance()->Destroy(this);
}
