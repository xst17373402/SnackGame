#pragma once

// Block对象用于定义一个像素块
class Block
{
public:
    Block()
    {
        block_x     = 0;
        block_y     = 0;
        block_state = 0;
    };
    Block(unsigned int x, unsigned int y)
    {
        block_x     = x;
        block_y     = y;
        block_state = 0;
    }
    Block(const Block& block_in)
    {
        this->block_x     = block_in.block_x;
        this->block_y     = block_in.block_y;
        this->block_state = 0;
    }
    Block& operator=(const Block& block_in)
    {
        this->block_x     = block_in.block_x;
        this->block_y     = block_in.block_y;
        this->block_state = 0;
    }
    unsigned int GetBlockX() const;
    unsigned int GetBlockY() const;
    unsigned int GetBlockSize() const;
    bool         BlockMoveUp();
    bool         BlockMoveDown();
    bool         BlockMoveLeft();
    bool         BlockMoveRight();
    void         KeepGoing();
    bool         IsBlock(unsigned int x, unsigned int y) const;

private:
    unsigned int block_x;
    unsigned int block_y;
    unsigned int
        block_state;  // 记录Block的状态 静止/MoveUp/MoveDown/MoveLeft/MoveRight
};