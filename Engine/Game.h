#pragma once
#include <chrono>

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "Apple.h"
#include "Panel.h"
#include "Snake.h"

class Game
{
public:
    Game(class MainWindow& wnd);
    Game(const Game&)            = delete;
    Game& operator=(const Game&) = delete;
    void  Go();

private:
    void ComposeFrame();
    void UpdateModel();
    /********************************/
    /*  User Functions              */
    /********************************/
private:
    MainWindow& wnd;
    Graphics    gfx;

    /********************************/
    /*  User Variables              */
    /********************************/
    Snake snake;
    Apple apple;

    Panel m_panel;

    std::chrono::steady_clock::time_point m_last_time;
    static constexpr size_t               k_max_fps = 20;
    static constexpr float k_max_fps_delta_time     = 1.0f / (float)k_max_fps;
};