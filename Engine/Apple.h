#pragma once
#include <random>

class Apple
{
public:
    Apple() : apple_x{ rand() % 10 }, apple_y{ rand() % 10 } {}
    Apple(const Apple&)            = delete;
    Apple& operator=(const Apple&) = delete;

    unsigned int GetAppleX() const { return apple_x; }
    unsigned int GetAppleY() const { return apple_y; }

    void RePlace(size_t rows, size_t cols);

private:
    int32_t apple_x;
    int32_t apple_y;
};