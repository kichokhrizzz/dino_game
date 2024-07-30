#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <SDL2/SDL_image.h>

class Obstacle
{
public:
    Obstacle(int x, int y, int w, int h, float speed, SDL_Renderer *renderer);
    ~Obstacle();
    void update();
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect() const;
    void setSpeed(float speed);

private:
    SDL_Rect obstacleRect;
    float speed;
    SDL_Texture *frames[10];
    int currentFrame;
    int frameCount;
    Uint32 lastFrameTime;
};

#endif