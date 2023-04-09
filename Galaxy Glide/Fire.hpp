#ifndef FIRE_H
#define FIRE_H

#include "Core.hpp"
#include "LTexture.hpp"
class Fire
{
public:
    Fire(float _x, float _y, float _velX, float _velY);
    ~Fire();
    void Update();
    void Render();

private:
    float xPos, yPos;
    float velocityX, velocityY;
    LTexture fireTex;
    SDL_Rect srcRect, destRect;
};

#endif // ROCK_H
