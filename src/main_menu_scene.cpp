#include "main_menu_scene.h"
#include "game_scene.h"
#include "config.h"

MainMenuScene::MainMenuScene(SceneManager &manager) : Scene(manager)
{
    playButton = {
        Config::SCREEN_WIDTH / 2.5f,
        Config::SCREEN_HEIGHT / 2.5f,
        100,
        50};

    settingsButton = {
        Config::SCREEN_WIDTH / 2.5f,
        Config::SCREEN_HEIGHT / 2.5f + 70,
        100,
        50};
}

void MainMenuScene::onEnter()
{
}

void MainMenuScene::onExit()
{
}

void MainMenuScene::update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (isPlayButtonClicked())
        {
            sceneManager.changeScene(SceneManager::SceneType::GAME);
        }
        else if (isSettingsButtonClicked())
        {
            // todo change to settings scene
        }
    }
}

void MainMenuScene::render()
{
    DrawRectangleRec(playButton, GRAY);
    DrawText("Play",
             playButton.x + 30,
             playButton.y + 15,
             20,
             WHITE);

    DrawRectangleRec(settingsButton, GRAY);
    DrawText("Settings",
             settingsButton.x + 10,
             settingsButton.y + 15,
             20,
             WHITE);
}

bool MainMenuScene::isPlayButtonClicked() const
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, playButton);
}

bool MainMenuScene::isSettingsButtonClicked() const
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, settingsButton);
}