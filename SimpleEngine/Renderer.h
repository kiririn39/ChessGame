#pragma once
#include <set>

#include "Components/IRenderComponent.h"


class Renderer
{
private:
    struct RenderComponentComparator
    {
        bool operator()(const IRenderComponent* a, const IRenderComponent* b) const;
    };

    std::multiset<IRenderComponent*, RenderComponentComparator> renderComponents;

public:
    void Render();
    void AddRenderComponent(IRenderComponent* renderComponent);
    void RemoveRenderComponent(IRenderComponent* renderComponent);
};
