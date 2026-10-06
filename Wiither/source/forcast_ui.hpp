#pragma once

#include "renderer.hpp"

class ForcastUI
{
public:
    ForcastUI();

    void Init(Renderer& renderer);
    void Update();
    Void Draw();

private:
    Renderer* m_renderer;
    bool m_initialized;
};