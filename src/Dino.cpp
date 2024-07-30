#include "Dino.h"
#include "Constants.h"
#include <SDL2/SDL_image.h>

Dino::Dino(SDL_Renderer *renderer) : dinoRect{100, GROUND_LEVEL, 50, 50}, yVel(0), isJumping(false), currentFrame(0), frameCount(6), lastFrameTime(0)
{

    const char *fileNames[6] = {
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-1.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-2.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-3.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-4.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-5.png",
        "/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/player-run-6.png",
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

Dino::~Dino()
{
    for (int i = 0; i < frameCount; ++i)
    {
        SDL_DestroyTexture(frames[i]);
    }
}

void Dino::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !isJumping)
    {
        yVel = JUMP_VELOCITY;
        isJumping = true;
    }
}

void Dino::update()
{
    if (isJumping)
    {
        dinoRect.y += yVel;
        yVel += GRAVITY;
        if (dinoRect.y >= GROUND_LEVEL)
        {
            dinoRect.y = GROUND_LEVEL;
            isJumping = false;
            yVel = 0;
        }
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= 100)
    {
        currentFrame = (currentFrame + 1) % frameCount;
        lastFrameTime = currentTime;
    }
}

void Dino::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, frames[currentFrame], nullptr, &dinoRect);
}

bool Dino::checkCollision(const SDL_Rect &otherRect) const
{
    SDL_Rect adjustedOtherRect = otherRect;
    adjustedOtherRect.w /= 2;

    return dinoRect.x < adjustedOtherRect.x + adjustedOtherRect.w &&
           dinoRect.x + dinoRect.w > adjustedOtherRect.x &&
           dinoRect.y < adjustedOtherRect.y + adjustedOtherRect.h &&
           dinoRect.y + dinoRect.h > adjustedOtherRect.y;
}
