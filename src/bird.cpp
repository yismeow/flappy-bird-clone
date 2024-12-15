#include "bird.h"
#include <iostream>

Bird::Bird()
    : position(Config::BIRD_START_POSITION),
      velocityY(0.0f),
      rotationAngle(0.0f),
      currentTextureIndex(1),
      timeSinceLastFrameChange(0.0f),
      currentState(State::falling),
      isJumping(false)
{
}

Bird::~Bird()
{
    for (int i = 0; i < framesAmount; i++)
        UnloadTexture(textures[i]);
}

void Bird::loadAssets()
{
    const char *texturePaths[framesAmount] = {
        "sprites/bluebird-downflap.png",
        "sprites/bluebird-midflap.png",
        "sprites/bluebird-upflap.png"};

    for (int i = 0; i < framesAmount; i++)
    {
        textures[i] = LoadTexture(texturePaths[i]);
        if (textures[i].id == 0)
        {
            std::cerr << "Failed to load texture at: " << texturePaths[i] << "\n";
            std::abort();
        }
    }
}

void Bird::update()
{
    switch (currentState)
    {
    case State::jumping:
        handleJumpingState();
        break;
    case State::falling:
        handleFallingState();
        break;
    }
}

void Bird::handleJumpingState()
{
    timeSinceLastFrameChange += GetFrameTime();
    handleJumping();
    handleJumpAnimation();
    updateRotation();

    if (velocityY > 0)
        currentState = State::falling;
}

void Bird::handleFallingState()
{
    handleJumping();
    updateRotation();
}

void Bird::jump()
{
    velocityY = -jumpStrength;
    currentTextureIndex = 0;
    isJumping = true;
    currentState = State::jumping;
}

void Bird::draw() const
{
    float textureWidth = textures[currentTextureIndex].width;
    float textureHeight = textures[currentTextureIndex].height;

    DrawTexturePro(textures[currentTextureIndex],
                   (Rectangle){0, 0, textureWidth, textureHeight},
                   (Rectangle){position.x, (float)position.y, textureWidth, textureHeight},
                   {textureWidth / 2.0f, textureHeight / 2.0f},
                   rotationAngle,
                   WHITE);
}

void Bird::reset()
{
    position = Config::BIRD_START_POSITION;
    velocityY = 0.0f;
    rotationAngle = 0.0f;
    currentTextureIndex = 1;
    timeSinceLastFrameChange = 0.0f;
    currentState = State::falling;
    isJumping = false;
}

void Bird::handleJumping()
{
    velocityY += gravityForce;
    position.y += velocityY;
}

void Bird::handleJumpAnimation()
{
    if (!isJumping)
        return;

    timeSinceLastFrameChange += GetFrameTime();
    if (timeSinceLastFrameChange > animationSpeed)
    {
        timeSinceLastFrameChange = 0.0f;

        currentTextureIndex++;
        if (currentTextureIndex == 3)
        {
            currentTextureIndex = 1;
            isJumping = false;
        }
    }
}

void Bird::updateRotation()
{
    if (currentState == State::falling)
        rotationAngle = std::min(rotationAngle + rotationSpeed, maxRotationAngle);
    else if (isJumping)
        rotationAngle = jumpRotationAngle;
}
