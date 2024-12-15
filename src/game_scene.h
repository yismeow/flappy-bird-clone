#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "game_over_scene.h"
#include "bird.h"
#include "pipe.h"
#include "ground.h"
#include "config.h"
#include "raylib.h"

class GameScene : public Scene
{
public:
    struct GameObjectsFlags
    {
        bool toUpdateBird = true;
        bool toUpdatePipes = true;
        bool toUpdateGround = true;
        bool toDrawPipes = true;
        bool toPlaySounds = true;
        bool autoPilot = false;
    };

private:
    GameObjectsFlags gameObjectsFlags;

    Bird bird;
    Ground ground;
    Pipe pipes[Config::PIPE_AMOUNT];

    int score = 0;
    bool isOver = false;

    Texture2D background;
    Texture2D digitFonts[10];
    Sound scoreSound;
    Sound birdDiedSound;
    Sound birdJumpSound;

    float lastTime = 0;
    float pipeTimerTime = Config::PIPE_TIMER_TIME;
    float pipeOffset = Config::PIPE_START_OFFSET;

    void loadAssets();
    void handleInput();
    void updateGameState();
    void updatePipes();
    void handlePipeSpawning();
    void spawnPipePair();
    void handleAutoPilot();

    void handleCollisions();
    void handleBirdCollisions();
    void handlePipeCollisions();

    void drawBackground();
    void drawPipes();
    void drawBird();
    void drawScore();

public:
    GameScene(SceneManager &manager);
    GameScene(GameScene &&) noexcept = default;
    GameScene &operator=(GameScene &&) noexcept = default;
    ~GameScene();

    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

    bool isGameOver() const { return isOver; }
    int getScore() const { return score; }
    void increaseScore();
    void setVolume(float volume);
    void setFlags(const GameObjectsFlags &flags);
    void reset();
};