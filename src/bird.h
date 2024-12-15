#pragma once
#include "raylib.h"
#include "config.h"

class Bird
{
public:
    enum class State
    {
        jumping,
        falling
    };

    Bird();
    ~Bird();

    void loadAssets();
    void update();
    void draw() const;
    void reset();
    void jump();

    float getWidth() const { return textures[0].width; }
    float getHeight() const { return textures[0].height; }

private:
    void handleJumpingState();
    void handleFallingState();
    void handleJumping();
    void handleJumpAnimation();
    void updateRotation();

public:
    Vector2 position;
    Texture2D textures[3];
    float velocityY;
    float rotationAngle;

private:
    int currentTextureIndex;
    int framesAmount = 3;
    float timeSinceLastFrameChange;
    State currentState;
    bool isJumping;

    const float gravityForce = Config::BIRD_GRAVITY_FORCE;
    const float jumpStrength = Config::BIRD_JUMP_STRENGTH;
    const float jumpRotationAngle = Config::BIRD_JUMP_ROTATION_ANGLE;
    const float maxRotationAngle = Config::MAX_BIRD_ROTATION_ANGLE;
    const float rotationSpeed = Config::BIRD_ROTATION_SPEED;

    float animationSpeed = Config::BIRD_ANIMATION_SPEED;
};
