#include "forcast_ui.hpp"

ForcastUI::ForcastUI() : m_renderer(nullptr), m_initialized(false)
{
}

void ForcastUI::Init(Renderer& renderer)
{
    m_renderer = &renderer;

    m_initialized = true;
}

void ForcastUI::Update()
{
    if (!m_initialized)
        return;

    // TODO: libwiigui init and widget updates
}

void ForcastUI::Draw()
{
    if (!m_initialized)
        return;

    // TODO: libwiigui will draw widgets here
}
