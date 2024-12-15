#pragma once
#include "raylib.h"
#include "config.h"

class Ground
{
public:
    ~Ground();
    void loadTexture();
    void update();
    void draw() const;
    float getWidth() const { return texture1.width; }
    float getHeight() const { return texture1.height; }
    void reset();

public:
    int y;
    Texture2D texture1;
    Texture2D texture2;

private:
    int x1;
    int x2;

    int speed = Config::GROUND_SCROLLING_SPEED;
};