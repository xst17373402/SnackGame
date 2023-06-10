/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20
 ** Game.cpp
 ** Copyright 2016 PlanetChili.net <http://www.planetchili.net>
 **
 *																						  *
 *	This file is part of The Chili DirectX Framework.
 **
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it
 *and/or modify it under the terms of the GNU General Public License as
 *published by the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 **
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be
 *useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	GNU General
 *Public License for more details.
 **
 *																						  *
 *	You should have received a copy of the GNU General Public License along
 *with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.
 **
 ******************************************************************************************/
#include "Game.h"

#include <thread>

#include <windows.h>
#include "MainWindow.h"

Game::Game(MainWindow& wnd)
    : wnd(wnd)
    , gfx(wnd)
    , snake()
    , apple()
    , m_panel()
    , m_last_time(std::chrono::steady_clock::now())
{}

void Game::Go()
{
    auto curr_time = std::chrono::steady_clock::now();

    gfx.BeginFrame();
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();

    auto duration =
        std::chrono::duration<float>(curr_time - m_last_time).count();
    if (duration < k_max_fps_delta_time)
    {
        std::this_thread::sleep_for(
            std::chrono::duration<float>(k_max_fps_delta_time - duration));
    }

    m_last_time = curr_time;
}

void Game::UpdateModel()
{
    if (snake.isDead()) return;  // 目前的逻辑是snack死了就停了
    
    snake.processKeyboardInput(wnd.kbd);

    // 每次移动过后判断snack有没有吃到苹果
    snake.update(m_panel, apple);
}

void Game::ComposeFrame()
{
    // 画出apple的位置
    m_panel.Draw(gfx, apple.GetAppleX(), apple.GetAppleY(), 0, 255, 0);

    // 遍历snack的身体  画出snack
    for (auto it = snake.begin(), end = snake.end(); it != end; ++it)
    {
        int32_t x = it->first;
        int32_t y = it->second;
        m_panel.Draw(gfx, x, y, 255, 0, 0);
    }
}
