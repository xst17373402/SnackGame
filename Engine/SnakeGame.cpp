#include "SnakeGame.h"

bool Snack::IsSnackDie() const
{
    return this->snack_die;
}

bool Snack::IsSnackStop() const
{
    return (this->snack_state == 0);
}

void Snack::SnackMoveUp()
{
    if (snack_state == 2)  // snack在向下移动时 不能向上移动
    {
        move_success = 0;  // 本次移动失败
        return;
    }
    Block temp_block = this->snack_q.front();  // 将头部的block取出
    if (temp_block
            .BlockMoveUp())  // 如果temp_block移动成功，则放在链表的头部，并记录snack移动状态
    {
        snack_q.push_front(temp_block);
        move_success = 1;
        // snack_q.pop_back();
        snack_state = 1;
    }
    else
    {
        move_success = 0;
        snack_die =
            true;  // 如果temp_block没有移动成功，则说明碰到了窗口边框，蛇die
    }
}

void Snack::SnackMoveDown()
{
    if (snack_state == 1)
    {
        move_success = 0;  // 本次移动失败
        return;
    }
    Block temp_block = this->snack_q.front();
    if (temp_block.BlockMoveDown())
    {
        snack_q.push_front(temp_block);
        move_success = 1;
        // snack_q.pop_back();
        snack_state = 2;
    }
    else
    {
        move_success = 0;
        snack_die    = true;
    }
}

void Snack::SnackMoveLeft()
{
    if (snack_state == 4)
    {
        move_success = 0;  // 本次移动失败
        return;
    }
    Block temp_block = this->snack_q.front();
    if (temp_block.BlockMoveLeft())
    {
        snack_q.push_front(temp_block);
        move_success = 1;
        // snack_q.pop_back();
        snack_state = 3;
    }
    else
    {
        move_success = 0;
        snack_die    = true;
    }
}

void Snack::SnackMoveRight()
{
    if (snack_state == 3)
    {
        move_success = 0;  // 本次移动失败
        return;
    }
    Block temp_block = this->snack_q.front();
    if (temp_block.BlockMoveRight())
    {
        snack_q.push_front(temp_block);
        move_success = 1;
        // snack_q.pop_back();
        snack_state = 4;
    }
    else
    {
        move_success = 0;
        snack_die    = true;
    }
}

void Snack::SnackKeepMoving()  // 保持前一个状态继续移动
{
    Block temp_block = this->snack_q.front();
    switch (snack_state)
    {
    case 1:
    {
        SnackMoveUp();
        break;
    }
    case 2:
    {
        SnackMoveDown();
        break;
    }
    case 3:
    {
        SnackMoveLeft();
        break;
    }
    case 4:
    {
        SnackMoveRight();
        break;
    }
    default: break;
    }
}

bool Snack::IsMoveSuccess() const
{
    return this->move_success;
}

void Snack::SnackGrow()
{
    this->snack_len++;
}

void Snack::SnackTryEat(Apple& apple)
{
    if (IsSnackDie()) return;
    if (!IsMoveSuccess()) return;
    if (GetHeadX() == apple.GetAppleX() && GetHeadY() == apple.GetAppleY())
    {
        apple.RePlace();
        SnackGrow();
    }
    else  // 如果没吃到，就要把尾部的block移除
    {
        snack_q.pop_back();
    }
}
unsigned int Snack::GetHeadX()
{
    return snack_q.front().GetBlockX();
}

unsigned int Snack::GetHeadY()
{
    return snack_q.front().GetBlockY();
}

unsigned int Snack::GetSnackSize()
{
    return snack_q.front().GetBlockSize();
}

std::list<Block>::iterator Snack::GetHead()
{
    return this->snack_q.begin();
}

std::list<Block>::iterator Snack::GetEnd()
{
    return this->snack_q.end();
}

void Snack::processKeyboardInput(const Keyboard& kbd)
{
    if (kbd.KeyIsPressed(VK_UP))
    {
        SnackMoveUp();
    }
    else if (kbd.KeyIsPressed(VK_DOWN))
    {
        SnackMoveDown();
    }
    else if (kbd.KeyIsPressed(VK_LEFT))
    {
        SnackMoveLeft();
    }
    else if (kbd.KeyIsPressed(VK_RIGHT))
    {
        SnackMoveRight();
    }
    else
    {
        SnackKeepMoving();
    }
}

unsigned int Snack::GetLength()
{
    return this->snack_len;
}
