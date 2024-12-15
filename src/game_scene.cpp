#include "game_scene.h"
#include <string>
#include <iostream>

GameScene::GameScene(SceneManager &manager)
    : Scene(manager)
{
    loadAssets();
    setVolume(0.1f);
}

GameScene::~GameScene()
{
    UnloadTexture(background);
    for (int i = 0; i < 10; i++)
    {
        UnloadTexture(digitFonts[i]);
    }
    UnloadSound(scoreSound);
    UnloadSound(birdDiedSound);
    UnloadSound(birdJumpSound);
}

void GameScene::loadAssets()
{
    bird.loadAssets();
    ground.loadTexture();
    background = LoadTexture("sprites/background-day.png");

    for (int i = 0; i < Config::PIPE_AMOUNT; i++)
    {
        pipes[i].loadTexture();
    }

    for (int i = 0; i < 10; i++)
    {
        std::string digitFilename = "sprites/" + std::to_string(i) + ".png";
        digitFonts[i] = LoadTexture(digitFilename.c_str());
    }

    scoreSound = LoadSound("audio/point.wav");
    birdDiedSound = LoadSound("audio/die.wav");
    birdJumpSound = LoadSound("audio/wing.wav");
}

void GameScene::onEnter()
{
    if (gameObjectsFlags.autoPilot)
        bird.position.y += Config::BIRD_JUMP_STRENGTH * 2 + 60.0f;
    bird.jump();
    if (gameObjectsFlags.toPlaySounds)
        PlaySound(birdJumpSound);
}

void GameScene::onExit()
{
}

void GameScene::update()
{
    if (isOver)
    {
        sceneManager.changeScene(SceneManager::SceneType::GAME_OVER, score);
        isOver = false;
        return;
    }

    if (gameObjectsFlags.autoPilot)
        handleAutoPilot();
    else
        handleInput();

    updateGameState();
}

void GameScene::render()
{
    drawBackground();
    if (gameObjectsFlags.toDrawPipes)
        drawPipes();
    ground.draw();
    drawBird();
    if (gameObjectsFlags.toUpdatePipes)
        drawScore();
}

void GameScene::handleInput()
{
    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        bird.jump();
        if (gameObjectsFlags.toPlaySounds)
            PlaySound(birdJumpSound);
    }
}

void GameScene::updateGameState()
{
    if (gameObjectsFlags.toUpdatePipes)
    {
        updatePipes();
        handleCollisions();
        handlePipeSpawning();
    }
    if (gameObjectsFlags.toUpdateBird)
        bird.update();
    if (gameObjectsFlags.toUpdateGround)
        ground.update();
}

void GameScene::updatePipes()
{
    for (auto &pipe : pipes)
    {
        if (pipe.active)
            pipe.update();
    }
}

void GameScene::handlePipeSpawning()
{
    float currentTime = GetTime() + 3;
    if (currentTime - lastTime > pipeTimerTime)
    {
        lastTime = currentTime;
        spawnPipePair();
    }
}

void GameScene::spawnPipePair()
{
    for (int i = 0; i < Config::PIPE_AMOUNT - 1; i += 2)
    {
        if (pipes[i].active)
            continue;

        float random_y = GetRandomValue(240, 380);

        pipes[i].position = Vector2{Config::SCREEN_WIDTH + Config::PIPE_SPAWN_OFFSET, random_y};
        pipes[i].active = true;
        pipes[i].scored = false;

        pipes[i + 1].position = Vector2{Config::SCREEN_WIDTH + Config::PIPE_SPAWN_OFFSET, random_y - pipeOffset};
        pipes[i + 1].active = true;
        pipes[i + 1].scored = false;
        pipes[i + 1].isTopPipe = true;

        pipeOffset = std::max(pipeOffset - 0.25f, Config::MAX_PIPE_OFFSET);
        return;
    }
}

void GameScene::handleAutoPilot()
{
    float jumpPeriod = 0.57f;
    static float timeSinceLastJump = 0.0f;
    timeSinceLastJump += GetFrameTime();

    if (timeSinceLastJump > jumpPeriod)
    {
        bird.jump();
        timeSinceLastJump = 0;
    }
}

void GameScene::handleCollisions()
{
    handleBirdCollisions();
    handlePipeCollisions();
}

void GameScene::handleBirdCollisions()
{
    bool hitGround = bird.position.y + bird.getHeight() >= Config::SCREEN_HEIGHT - ground.getHeight();
    bool hitCeiling = bird.position.y <= 0;

    if (hitGround || hitCeiling)
    {
        if (gameObjectsFlags.toPlaySounds)
            PlaySound(birdDiedSound);
        isOver = true;
    }
}

void GameScene::handlePipeCollisions()
{
    for (int i = 0; i < Config::PIPE_AMOUNT - 1; i += 2)
    {
        if (!pipes[i].active)
            continue;

        bool isAlignedWithPipe = (bird.position.x + bird.getWidth() > pipes[i].position.x + 15.0f &&
                                  bird.position.x < pipes[i].position.x + pipes[0].getWidth());
        if (!isAlignedWithPipe)
            continue;

        bool isPastPipe = bird.position.x + bird.getWidth() > pipes[i].position.x + pipes[0].getWidth() + 30;
        bool isInMiddle = (bird.position.y + bird.getHeight() < pipes[i].position.y - 5.0f) &&
                          (bird.position.y > pipes[i + 1].position.y + 18.0f);

        if (isInMiddle)
        {
            if (isPastPipe && !pipes[i].scored)
            {
                increaseScore();
                if (gameObjectsFlags.toPlaySounds)
                    PlaySound(scoreSound);
                pipes[i].scored = true;
            }
        }
        else
        {
            if (gameObjectsFlags.toPlaySounds)
                PlaySound(birdDiedSound);
            isOver = true;
        }
    }
}

void GameScene::drawBackground()
{
    DrawTexture(background, 0, 0, WHITE);
}

void GameScene::drawPipes()
{
    for (const auto &pipe : pipes)
    {
        if (pipe.active)
            pipe.draw();
    }
}

void GameScene::drawBird()
{
    bird.draw();
}

void GameScene::drawScore()
{
    std::string scoreStr = std::to_string(score);
    int xPosition = Config::SCORE_X_POSITION;

    for (char c : scoreStr)
    {
        int digit = c - '0';
        DrawTexture(digitFonts[digit], xPosition, Config::SCORE_Y_POSITION, WHITE);
        xPosition += digitFonts[digit].width + Config::SCORE_DIGITS_OFFSET;
    }
}

void GameScene::increaseScore()
{
    score++;
}

void GameScene::setVolume(float volume)
{
    SetSoundVolume(scoreSound, volume);
    SetSoundVolume(birdDiedSound, volume);
    SetSoundVolume(birdJumpSound, volume);
}

void GameScene::setFlags(const GameObjectsFlags &flags)
{
    gameObjectsFlags = flags;
}

void GameScene::reset()
{
    score = 0;
    isOver = false;
    lastTime = 0;

    bird.reset();
    ground.reset();
    for (auto &pipe : pipes)
        pipe.reset();

    gameObjectsFlags = {
        .toUpdateBird = true,
        .toUpdatePipes = true,
        .toUpdateGround = true,
        .toDrawPipes = true,
        .toPlaySounds = true};
}
