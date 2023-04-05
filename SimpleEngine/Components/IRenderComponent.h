#pragma once

class IRenderComponent
{
public:
    virtual int GetRenderOrder() const = 0;
    virtual void Render() = 0;
};
