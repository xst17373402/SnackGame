#pragma once

#include <random>

class Apple
{
public:
    Apple()
    {
        apple_x = rand() % 10;
        apple_y = rand() % 20;
    }
    Apple(const Apple&)                  = delete;
    Apple&       operator=(const Apple&) = delete;
    unsigned int GetAppleX();
    unsigned int GetAppleY();
    unsigned int GetAppleSize();
    void         RePlace();

private:
    unsigned int apple_x;
    unsigned int apple_y;
};