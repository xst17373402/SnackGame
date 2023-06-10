#pragma once
#include <list>
#include <utility>

#include "Keyboard.h"
#include "Panel.h"
#include "Apple.h"

class Snake
{
private:
    enum SnakeDirection
    {
        _stop,
        _right,
        _left,
        _up,
        _down,
        _count,
    };
    using Pos = std::pair<int32_t, int32_t>;

public:
    explicit Snake(Pos pos = Pos{ 0, 0 }) : m_data{ pos } {}
    Snake(const Snake&)            = delete;
    Snake& operator=(const Snake&) = delete;

    bool   isDead() const { return m_is_dead; }
    size_t getSize() const { return m_data.size(); }

    void processKeyboardInput(const Keyboard& kbd);

    void update(const Panel& panel, const Apple& apple);

    auto begin() const { return m_data.begin(); }
    auto end() const { return m_data.end(); }

private:
    std::list<Pos> m_data;
    SnakeDirection m_state = _stop;

    bool m_is_dead = false;

    static constexpr int k_dirs[_count][2] = {
        { 0,  0},
        { 1,  0},
        {-1,  0},
        { 0, -1},
        { 0,  1}
    };
};