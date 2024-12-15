#include "game_over_scene.h"
#include "config.h"
#include <fstream>
#include <iostream>

GameOverScene::GameOverScene(SceneManager &manager, int score)
    : Scene(manager),
      finalScore(score)
{
    gameOverTexture = LoadTexture("sprites/gameover.png");

    std::ifstream file("bestscore.txt");
    if (file.is_open())
    {
        file >> bestScore;
        file.close();
    }
    else
        bestScore = 0;
}

GameOverScene::~GameOverScene()
{
    UnloadTexture(gameOverTexture);
}

void GameOverScene::onEnter()
{
    updateBestScore();
}

void GameOverScene::onExit()
{
}

void GameOverScene::update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (isMainMenuButtonClicked())
            sceneManager.changeScene(SceneManager::SceneType::MAIN_MENU);
        else
            sceneManager.changeScene(SceneManager::SceneType::GAME);
    }
    if (IsKeyPressed(KEY_SPACE))
        sceneManager.changeScene(SceneManager::SceneType::GAME);
}

void GameOverScene::render()
{
    DrawTexture(gameOverTexture,
                Config::SCREEN_WIDTH / 2 - gameOverTexture.width / 2,
                Config::SCREEN_HEIGHT / 4,
                RAYWHITE);

    DrawText(("Score: " + std::to_string(finalScore)).c_str(),
             Config::SCREEN_WIDTH / 3,
             Config::SCREEN_HEIGHT / 2,
             30,
             BLACK);

    DrawText(("Best: " + std::to_string(bestScore)).c_str(),
             Config::SCREEN_WIDTH / 3,
             Config::SCREEN_HEIGHT / 2 + 30,
             30,
             BLACK);

    DrawText("Press SPACE or CLICK to restart",
             5,
             Config::SCREEN_HEIGHT / 2 + 60,
             17,
             BLACK);

    DrawRectangle(Config::SCREEN_WIDTH * 2 / 3 - 100, Config::SCREEN_HEIGHT * 2 / 3, 100, 40, GRAY);
    DrawText("Menu", Config::SCREEN_WIDTH * 2 / 3 - 80, Config::SCREEN_HEIGHT * 2 / 3 + 10, 20, BLACK);
}

bool GameOverScene::isMainMenuButtonClicked() const
{
    Vector2 mousePos = GetMousePosition();
    Rectangle menuButton = {
        float(Config::SCREEN_WIDTH * 2 / 3 - 100),
        float(Config::SCREEN_HEIGHT * 2 / 3),
        100,
        40};

    return CheckCollisionPointRec(mousePos, menuButton);
}

void GameOverScene::updateBestScore()
{
    if (finalScore > bestScore)
    {
        bestScore = finalScore;
        std::ofstream file("bestscore.txt");
        if (file.is_open())
        {
            file << bestScore;
            file.close();
        }
    }
}