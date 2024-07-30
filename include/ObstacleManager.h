#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include <vector>
#include "Obstacle.h"
#include <SDL.h>

class ObstacleManager
{
public:
    ObstacleManager(SDL_Renderer *renderer);
    void update();
    void render(SDL_Renderer *renderer);
    const std::vector<Obstacle> &getObstacles() const;

private:
    std::vector<Obstacle> obstacles;
    Uint32 nextObstacleTime;
    float obstacleSpeed;
    Uint32 lastSpeedIncreaseTime;
    SDL_Renderer *renderer;
};

#endif