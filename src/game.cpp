#include "game.h"
#include "config.h"
#include "main_menu_scene.h"

Game::Game()
{
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Flappy Bird");
    InitAudioDevice();
    SetTargetFPS(Config::FPS);
    sceneManager.init();
    sceneManager.changeScene(SceneManager::SceneType::MAIN_MENU);
}

Game::~Game()
{
    CloseAudioDevice();
    CloseWindow();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        sceneManager.update();
        sceneManager.render();
    }
}