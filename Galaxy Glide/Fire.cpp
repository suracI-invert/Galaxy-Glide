#include "Fire.hpp"

Fire::Fire(float _x, float _y, float _velX, float _velY)
{
    fireTex.loadFromFile("/Users/raiju/Downloads/Bob.png");
    xPos = _x;
    yPos = _y;
    velocityX = _velX;
    velocityY = _velY;
}

Fire::~Fire()
{
    fireTex.free();
}

void Fire::Update()
{
    xPos += 2* velocityX;
    yPos += 2* velocityY;
    srcRect = {0,0,50,50};
    destRect = {(int)xPos, (int) yPos, 50,50};
}
void Fire::Render()
{
    SDL_RenderCopy(Core::gRenderer, fireTex.getTexture(), &srcRect, &destRect);
}
