#include "Block.h"

#include "SnakeGameConsts.h"

// 判断位置x，y是否存在Block，是为wall预留的函数，现在没添加墙的逻辑，所以没用到
bool Block::IsBlock(unsigned int x, unsigned int y) const
{
    return (x == this->block_x && y == this->block_y);
}

unsigned int Block::GetBlockX() const
{
    return this->block_x;
}

unsigned int Block::GetBlockY() const
{
    return this->block_y;
}

unsigned int Block::GetBlockSize() const
{
    //return this->block_size;
    return BlockSize;
}

bool Block::BlockMoveUp()  // block块向上移动
{
    if (this->block_y >
        0)  // block当前y大于0 才能向上移动，否则移动失败，返回false
    {
        this->block_y--;
        return true;
    }
    else
        return false;
}

bool Block::BlockMoveDown()
{
    if (this->block_y < (ScreenHeight / GetBlockSize() - 1))
    {
        this->block_y++;
        return true;
    }
    else
        return false;
}

bool Block::BlockMoveLeft()
{
    if (this->block_x > 0)
    {
        this->block_x--;
        return true;
    }
    else
        return false;
}

bool Block::BlockMoveRight()
{
    if (this->block_x < (ScreenWidth / GetBlockSize() - 1))
    {
        this->block_x++;
        return true;
    }
    else
        return false;
}

void Block::KeepGoing()  // 根据之前的移动状态 移动Block
{
    switch (block_state)
    {
    case 1:
    {
        BlockMoveUp();
        break;
    }
    case 2:
    {
        BlockMoveDown();
        break;
    }
    case 3:
    {
        BlockMoveLeft();
        break;
    }
    case 4:
    {
        BlockMoveRight();
        break;
    }
    default:
    {
        break;
    }
    }
}