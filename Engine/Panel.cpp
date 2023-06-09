#include "Panel.h"
#include <cassert>

Panel::Panel()
    : m_panel_width{ Graphics::ScreenWidth / k_block_size }
    , m_panel_height{ Graphics::ScreenHeight / k_block_size }
{}

void Panel::Draw(Graphics& gfx,
                 int32_t   x,
                 int32_t   y,
                 uint8_t   r,
                 uint8_t   g,
                 uint8_t   b)
{
    assert(0 <= x && x < m_panel_width);
    assert(0 <= y && y < m_panel_height);

    int32_t col = x * k_block_size;
    int32_t row = y * k_block_size;

    for (int32_t j = 0; j < k_block_size; ++j)
    {
        for (int32_t i = 0; i < k_block_size; ++i)
        {
            int32_t xx = col + i;
            int32_t yy = row + j;

            gfx.PutPixel(xx, yy, r, g, b);
        }
    }
}