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
#include <windows.h>
#include "MainWindow.h"

#include "Block.h"

Game::Game(MainWindow& wnd) : wnd(wnd), gfx(wnd), snack(), apple()
{}

void Game::Go()
{
    gfx.BeginFrame();
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel()
{
    if (snack.IsSnackDie()) return;  // 目前的逻辑是snack死了就停了
    Keyboard::Event event = wnd.kbd.ReadKey();  // 从kbd类中获取一个key事件
    // 如果是↑↓←→的按下事件，则改变snack移动方向
    if (event.IsPress())
    {
        unsigned char key_msg = event.GetCode();
        switch (key_msg)
        {
        case VK_UP:
        {
            snack.SnackMoveUp();
            break;
        }
        case VK_DOWN:
        {
            snack.SnackMoveDown();
            break;
        }
        case VK_LEFT:
        {
            snack.SnackMoveLeft();
            break;
        }
        case VK_RIGHT:
        {
            snack.SnackMoveRight();
            break;
        }
        default:
        {
            snack.SnackKeepMoving();
            break;
        }
        }
    }
    else
    {
        snack.SnackKeepMoving();
    }

    // 每次移动过后判断snack有没有吃到苹果
    snack.SnackTryEat(apple);
}

void Game::ComposeFrame()
{
    unsigned int snack_len = snack.GetLength();
    // 根据snack_len 控制休眠时间，snack_len越大 刷新速度越快
    if (30 > 60 - 3 * snack_len)
        Sleep(30);
    else
        Sleep(60 - 3 * snack_len);

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
