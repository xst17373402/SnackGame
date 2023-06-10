#include "ChiliWin.h"

#include "Snake.h"
#include <cassert>

void Snake::processKeyboardInput(const Keyboard& kbd)
{
    if (kbd.KeyIsPressed(VK_UP))
    {
        if (m_state != _down) m_state = _up;
    }
    else if (kbd.KeyIsPressed(VK_DOWN))
    {
        if (m_state != _up) m_state = _down;
    }
    else if (kbd.KeyIsPressed(VK_LEFT))
    {
        if (m_state != _right) m_state = _left;
    }
    else if (kbd.KeyIsPressed(VK_RIGHT))
    {
        if (m_state != _left) m_state = _right;
    }
}

void Snake::update(const Panel& panel, const Apple& apple)
{
    const auto dir = k_dirs[m_state];
    {
        Pos     head = m_data.front();
        int32_t nx   = head.first + dir[0];
        int32_t ny   = head.second + dir[1];

        if (!panel.isInPanel(nx, ny))
        {
            m_is_dead = true;
            return;
        }

        m_data.emplace_front(nx, ny);

        int32_t ax = apple.GetAppleX();
        int32_t ay = apple.GetAppleY();
        if (ax != nx || ay != ny)
        {
            m_data.pop_back();
        }
    }
}