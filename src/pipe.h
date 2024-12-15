#pragma once
#include "raylib.h"
#include "config.h"

class Pipe
{
public:
    ~Pipe();
    void loadTexture();
    void update();
    void draw() const;
    void reset();
    float getWidth() const { return texture.width; }
    float getHeight() const { return texture.height; }

public:
    Vector2 position;
    Texture2D texture;
    bool active = false;
    bool isTopPipe = false;
    bool scored = false;

private:
    int speed = Config::PIPE_SPEED;
};