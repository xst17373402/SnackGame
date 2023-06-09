#pragma once
#include <list>
#include <utility>
#include <vector>

#include "Graphics.h"
#include "Keyboard.h"

#include "Block.h"
#include "Apple.h"

class Snack  // 蛇对象
{
private:
    enum class SnakeDirection
    {
        Stop,
        Right,
        Left,
        Up,
        Down
    };

public:
    Snack()
    {
        Block block(0, 0);
        snack_q.push_back(block);
    }
    Snack(unsigned int start_x, unsigned int start_y)
    {
        Block block(start_x, start_y);
        snack_q.push_back(block);
    }

    Snack(const Snack&)            = delete;
    Snack& operator=(const Snack&) = delete;

    bool IsSnackDie() const;
    bool IsSnackStop() const;
    bool IsMoveSuccess() const;

private:
    void SnackMoveUp();
    void SnackMoveDown();
    void SnackMoveLeft();
    void SnackMoveRight();
    void SnackKeepMoving();

public:
    void                       SnackGrow();
    void                       SnackTryEat(Apple& apple);
    unsigned int               GetHeadX();
    unsigned int               GetHeadY();
    unsigned int               GetSnackSize();
    unsigned int               GetLength();
    std::list<Block>::iterator GetHead();
    std::list<Block>::iterator GetEnd();

    void processKeyboardInput(const Keyboard& kbd);

private:
    std::list<Block> snack_q;  // 蛇对象的身体由一个block链表组成
    unsigned int     snack_len    = 1;
    bool             snack_die    = false;
    SnakeDirection   snack_state  = SnakeDirection::Stop;
    bool             move_success = false;  // 判断是否移动成功
};