#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "main_menu_scene.h"
#include "game_scene.h"
#include "raylib.h"

class GameOverScene : public Scene
{
private:
    Texture2D gameOverTexture;

    int finalScore;
    int bestScore;

public:
    GameOverScene(SceneManager &manager, int score);
    ~GameOverScene();

    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

    bool isMainMenuButtonClicked() const;
    void updateBestScore();
};
