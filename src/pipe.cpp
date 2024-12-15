#include "pipe.h"

Pipe::~Pipe()
{
    UnloadTexture(texture);
}

void Pipe::loadTexture()
{
    texture = LoadTexture("sprites/pipe-green.png");
}

void Pipe::update()
{
    position.x -= speed;
    if (position.x < -texture.width)
        active = false;
}

void Pipe::draw() const
{
    if (!isTopPipe)
        DrawTexture(texture, position.x, position.y, WHITE);
    else
    {
        Rectangle sourceRec = {0, 0, -(float)texture.width, -(float)texture.height};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};
        Vector2 origin = {0, (float)texture.height};
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
    }
}

void Pipe::reset()
{
    active = false;
    isTopPipe = false;
    scored = false;
}
