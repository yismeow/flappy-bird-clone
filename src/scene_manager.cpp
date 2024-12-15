#include "scene_manager.h"
#include "main_menu_scene.h"
#include "game_scene.h"
#include "game_over_scene.h"

void SceneManager::init()
{
    currentSceneTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    secondarySceneTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    menuScene = std::make_shared<MainMenuScene>(*this);
    gameScene = std::make_shared<GameScene>(*this);
    gameOverScene = std::make_shared<GameOverScene>(*this, 0);
}

SceneManager::~SceneManager()
{
    UnloadRenderTexture(currentSceneTexture);
    UnloadRenderTexture(secondarySceneTexture);
}

void SceneManager::changeScene(SceneType sceneType, int score)
{
    if (currentScene)
        currentScene->onExit();
    if (secondaryScene)
        secondaryScene->onExit();

    switch (sceneType)
    {
    case SceneType::MAIN_MENU:
        currentScene = menuScene;
        gameScene->reset();
        gameScene->setFlags({.toUpdateBird = true,
                             .toUpdatePipes = false,
                             .toUpdateGround = true,
                             .toDrawPipes = false,
                             .toPlaySounds = false,
                             .autoPilot = true});
        secondaryScene = gameScene;
        break;

    case SceneType::GAME:
        gameScene->reset();
        currentScene = gameScene;
        secondaryScene = nullptr;
        break;

    case SceneType::GAME_OVER:
        gameScene->setFlags({.toUpdateBird = false,
                             .toUpdatePipes = false,
                             .toUpdateGround = false,
                             .toDrawPipes = true,
                             .toPlaySounds = false,
                             .autoPilot = false});
        currentScene = gameOverScene;
        secondaryScene = gameScene;
        break;
    }

    if (currentScene)
        currentScene->onEnter();
    if (secondaryScene)
        secondaryScene->onEnter();
}

void SceneManager::update()
{
    if (currentScene)
        currentScene->update();
    if (secondaryScene)
        secondaryScene->update();
}

void SceneManager::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentScene)
    {
        BeginTextureMode(currentSceneTexture);
        ClearBackground(BLANK);
        currentScene->render();
        EndTextureMode();
    }

    if (secondaryScene)
    {
        BeginTextureMode(secondarySceneTexture);
        ClearBackground(BLANK);
        secondaryScene->render();
        EndTextureMode();
    }
    DrawTextureRec(secondarySceneTexture.texture,
                   Rectangle{0, 0, (float)secondarySceneTexture.texture.width, -(float)secondarySceneTexture.texture.height},
                   Vector2{0, 0}, Fade(WHITE, 0.5f));
    DrawTextureRec(currentSceneTexture.texture,
                   Rectangle{0, 0, (float)currentSceneTexture.texture.width, -(float)currentSceneTexture.texture.height},
                   Vector2{0, 0}, WHITE);
    EndDrawing();
}