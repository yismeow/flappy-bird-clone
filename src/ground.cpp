#include "ground.h"

Ground::~Ground()
{
    UnloadTexture(texture1);
    UnloadTexture(texture2);
}

void Ground::loadTexture()
{
    texture1 = LoadTexture("sprites/base.png");
    texture2 = texture1;
    x1 = 0;
    x2 = texture2.width;
    y = Config::SCREEN_HEIGHT - texture1.height;
}

void Ground::update()
{
    x1 -= speed;
    x2 -= speed;

    int width = texture1.width;
    if (x1 + width < 0)
        x1 += width * 2;
    else if (x2 + width < 0)
        x2 += width * 2;
}

void Ground::draw() const
{
    DrawTexture(texture1, x1, y, WHITE);
    DrawTexture(texture1, x2, y, WHITE);
}

void Ground::reset()
{
    x1 = 0;
    x2 = texture2.width;
}
