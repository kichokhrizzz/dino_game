#ifndef DINO_H
#define DINO_H

#include <SDL.h>

class Dino
{
public:
    Dino(SDL_Renderer *renderer);
    ~Dino();
    void handleEvent(SDL_Event &e);
    void update();
    void render(SDL_Renderer *renderer);
    bool checkCollision(const SDL_Rect &otherRect) const;

private:
    SDL_Rect dinoRect;
    int yVel;
    bool isJumping;
    SDL_Texture *frames[6];
    int currentFrame;
    int frameCount;
    Uint32 lastFrameTime;
};

#endif