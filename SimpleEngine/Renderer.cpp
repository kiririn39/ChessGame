#include "Renderer.h"

bool Renderer::RenderComponentComparator::operator()(const IRenderComponent* left, const IRenderComponent* right) const
{
    return left->GetRenderOrder() < right->GetRenderOrder();
}

void Renderer::Render()
{
    for (auto element : renderComponents)
        element->Render();

    renderComponents.clear();
}

void Renderer::AddRenderComponent(IRenderComponent* renderComponent)
{
    renderComponents.insert(renderComponent);
}

void Renderer::RemoveRenderComponent(IRenderComponent* renderComponent)
{
    renderComponents.insert(renderComponent);
}
