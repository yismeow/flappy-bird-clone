#pragma once
#include "scene.h"
#include "raylib.h"
#include "scene_manager.h"

class GameScene;

class MainMenuScene : public Scene
{
private:
    Rectangle playButton;
    Rectangle settingsButton;

public:
    MainMenuScene(SceneManager &manager);

    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

    bool isPlayButtonClicked() const;
    bool isSettingsButtonClicked() const;
};
