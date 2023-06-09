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

#include "Block.h"

Game::Game(MainWindow& wnd)
    : wnd(wnd)
    , gfx(wnd)
    , snack()
    , apple()
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
    if (snack.IsSnackDie()) return;  // 目前的逻辑是snack死了就停了
    
    snack.processKeyboardInput(wnd.kbd);

    // 每次移动过后判断snack有没有吃到苹果
    snack.SnackTryEat(apple);
}

void Game::ComposeFrame()
{
    // 画出apple的位置
    unsigned int size    = apple.GetAppleSize();
    unsigned int apple_x = size * apple.GetAppleX();
    unsigned int apple_y = size * apple.GetAppleY();

    for (unsigned int i = apple_x; i < apple_x + size; ++i)
    {
        for (unsigned int j = apple_y; j < apple_y + size; ++j)
        {
            gfx.PutPixel(i, j, 0, 255, 0);
        }
    }

    // 遍历snack的身体  画出snack
    size                                  = snack.GetSnackSize();
    std::list<Block>::iterator snack_head = snack.GetHead();
    std::list<Block>::iterator snack_end  = snack.GetEnd();
    for (std::list<Block>::iterator it = snack_head; it != snack_end; ++it)
    {
        Block        temp_block = *it;
        unsigned int x          = size * temp_block.GetBlockX();
        unsigned int y          = size * temp_block.GetBlockY();

        for (unsigned int i = x; i < x + size; ++i)
        {
            for (unsigned int j = y; j < y + size; ++j)
            {
                gfx.PutPixel(i, j, 255, 0, 0);
            }
        }
    }
}
