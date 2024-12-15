#pragma once

namespace Config
{
    // window
    constexpr int SCREEN_WIDTH = 288;
    constexpr int SCREEN_HEIGHT = 512;
    constexpr int FPS = 60;

    // bird
    constexpr float MAX_BIRD_ROTATION_ANGLE = 90.0f;
    constexpr float BIRD_ROTATION_SPEED = 5.0f;
    constexpr float BIRD_JUMP_ROTATION_ANGLE = -30.0f;
    constexpr float BIRD_GRAVITY_FORCE = .5f;
    constexpr int BIRD_JUMP_STRENGTH = 9;
    constexpr Vector2 BIRD_START_POSITION = {50, SCREEN_HEIGHT / 2};
    constexpr float BIRD_ANIMATION_SPEED = .2f;

    // ground
    constexpr int GROUND_SCROLLING_SPEED = 3;

    // pipe
    constexpr int PIPE_SPEED = 3;
    constexpr int PIPE_AMOUNT = 6;
    constexpr int PIPE_SPAWN_OFFSET = 100;
    constexpr float PIPE_START_OFFSET = 200.0f;
    constexpr float PIPE_TIMER_TIME = 1.0f;
    constexpr float MAX_PIPE_OFFSET = 100.0f;

    constexpr int SCORE_DIGITS_OFFSET = 5;
    constexpr int SCORE_X_POSITION = SCREEN_WIDTH / 2;
    constexpr int SCORE_Y_POSITION = 30;
}