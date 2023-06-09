#include "Apple.h"

#include "SnakeGameConsts.h"

unsigned int Apple::GetAppleX()
{
    return this->apple_x;
}

unsigned int Apple::GetAppleY()
{
    return this->apple_y;
}

unsigned int Apple::GetAppleSize()
{
    //return this->apple_size;
    return BlockSize;
}

void Apple::RePlace()  // 重新随机放置apple位置
{
    this->apple_x = rand() % (ScreenWidth / BlockSize);
    this->apple_y = rand() % (ScreenHeight / BlockSize);
}