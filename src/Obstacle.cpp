#include "Obstacle.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Constants.h"

Obstacle::Obstacle(int x, int y, int w, int h, float speed, SDL_Renderer *renderer)
    : obstacleRect{x, y, w, h}, speed(speed), currentFrame(0), frameCount(10), lastFrameTime(0)
{
    const char *fileNames[10] = {
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-1.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-2.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-3.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-4.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-5.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-6.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-7.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-8.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-9.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/frog-10.png",
    };

    for (int i = 0; i < frameCount; ++i)
    {
        SDL_Surface *surface = IMG_Load(fileNames[i]);
        if (!surface)
        {
            SDL_Log("Unable to load image %s! SDL_image Error: %s\n", fileNames[i], IMG_GetError());
            return;
        }
        frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
    obstacleRect.x -= speed;
    if (obstacleRect.x + obstacleRect.w < 0)
    {
        obstacleRect.x = SCREEN_WIDTH;
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= 100)
    {
        currentFrame = (currentFrame + 1) % frameCount;
        lastFrameTime = currentTime;
    }
}

void Obstacle::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, frames[currentFrame], nullptr, &obstacleRect);
}

SDL_Rect Obstacle::getRect() const
{
    return obstacleRect;
}

void Obstacle::setSpeed(float newSpeed)
{
    speed = newSpeed;
}