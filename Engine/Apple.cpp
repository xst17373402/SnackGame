#include "Apple.h"

void Apple::RePlace(size_t rows, size_t cols)  // 重新随机放置apple位置
{
    this->apple_x = rand() % cols;
    this->apple_y = rand() % rows;
}