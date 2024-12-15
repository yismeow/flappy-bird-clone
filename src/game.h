#pragma once
#include "raylib.h"
#include "scene_manager.h"

class Game
{
private:
    SceneManager sceneManager;

public:
    Game();
    ~Game();
    void run();
};