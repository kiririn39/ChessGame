#include "GameObject.h"

#include <cassert>
#include <format>
#include <ranges>

#include "EngineCore.h"
#include "Logger.h"

bool GameObject::IsInvalid()
{
    return isInvalid;
}

void GameObject::Destroy()
{
    EngineCore::GetInstance()->Destroy(this);
}

void GameObject::AddChildGameObject(GameObject* object)
{
    if (object == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING,
                                  std::format("Gameobject: {} you are trying to add null child", Name));
        return;
    }

    if (object == this)
        return;

    if (std::ranges::find(Children, object) != Children.end())
        return;

    object->Parent = this;
    Children.push_back(object);
}

void GameObject::RemoveChildGameObject(GameObject* object)
{
    if (object == nullptr)
    {
        Logger::LogWithStackTrace(Level::LOG_WARNING,
                                  std::format("Gameobject: {} you are trying to remove null child", Name));
        return;
    }

    if (object == this)
        return;

    auto match = std::ranges::find(Children, object);

    if (match == Children.end())
        return;

    object->Parent = nullptr;
    Children.erase(match);
}

void GameObject::Unparent()
{
    if (Parent == nullptr)
        return;

    Parent->RemoveChildGameObject(this);
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
