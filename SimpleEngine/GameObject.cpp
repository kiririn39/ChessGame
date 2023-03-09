#include "GameObject.h"

#include <cassert>
#include <ranges>

#include "Engine.h"

void GameObject::Destroy()
{
    Engine::GetInstance()->Destroy(this);
}

void GameObject::AddChildGameObject(GameObject* object)
{
    assert(object != nullptr);

    if (std::ranges::find(Children, object) != Children.end())
        return;

    object->Parent = this;
    Children.push_back(object);
}

void GameObject::RemoveChildGameObject(GameObject* object)
{
    assert(object != nullptr);

    auto match = std::ranges::find(Children, object);

    if (match == Children.end())
        return;

    object->Parent = nullptr;
    Children.erase(match);
}

GameObject* GameObject::GetChildGameObject(uint16_t index) const
{
    assert(index <= GetChildrenCount() - 1);

    return Children.at(index);
}

size_t GameObject::GetChildrenCount() const
{
    return Children.size();
}

GameObject* GameObject::GetParent() const
{
    return Parent;
}

auto GameObject::GetChildren() const
{
    return Children | std::ranges::views::all;
}
