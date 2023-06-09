#pragma once
#include <utility>

#include "Graphics.h"

#include "Apple.h"

class Panel
{
public:
    Panel();
    Panel(const Panel&)            = delete;
    Panel& operator=(const Panel&) = delete;

    std::pair<int32_t, int32_t> GetSize() const
    {
        return { m_panel_width, m_panel_height };
    }

public:
    void Draw(Graphics& gfx,
              int32_t   x,
              int32_t   y,
              uint8_t   r,
              uint8_t   g,
              uint8_t   b);

    bool isInPanel(int32_t x, int32_t y) const
    {
        return (0 <= x && x < m_panel_width && 0 <= y && y < m_panel_height);
    }

private:
    static constexpr int32_t k_block_size = 20;

    int32_t m_panel_width;
    int32_t m_panel_height;
};
