#pragma once
#include "scene.h"
#include "raylib.h"
#include <memory>
#include <array>

class MainMenuScene;
class GameScene;
class GameOverScene;

class SceneManager
{
public:
    enum class SceneType
    {
        MAIN_MENU,
        GAME,
        GAME_OVER,
        SETTINGS,
    };

    ~SceneManager();
    void init();
    void changeScene(SceneType sceneType, int score = 0);
    void update();
    void render();

private:
    std::shared_ptr<Scene> currentScene;
    std::shared_ptr<Scene> secondaryScene;
    RenderTexture2D currentSceneTexture;
    RenderTexture2D secondarySceneTexture;

    std::shared_ptr<MainMenuScene> menuScene;
    std::shared_ptr<GameScene> gameScene;
    std::shared_ptr<GameOverScene> gameOverScene;
};
