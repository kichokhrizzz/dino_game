#include "ObstacleManager.h"
#include <cstdlib>
#include <ctime>
#include "Constants.h"
#include <iostream>

ObstacleManager::ObstacleManager(SDL_Renderer *renderer)
    : renderer(renderer)
{
    std::srand(static_cast<unsigned>(std::time(0)));
    nextObstacleTime = SDL_GetTicks() + (std::rand() % 3000 + 1000);
    obstacleSpeed = 5.0f;
    lastSpeedIncreaseTime = SDL_GetTicks();
}

void ObstacleManager::update()
{
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastSpeedIncreaseTime >= 10000)
    {
        obstacleSpeed += 1.0f;
        lastSpeedIncreaseTime = currentTime;
    }
    if (obstacles.size() < MAX_OBSTACLES && currentTime >= nextObstacleTime)
    {
        bool canGenerate = true;

        if (!obstacles.empty())
        {
            const Obstacle &lastObstacle = obstacles.back();
            if (SCREEN_WIDTH - (lastObstacle.getRect().x + lastObstacle.getRect().w) < MIN_OBSTACLE_DISTANCE)
            {
                canGenerate = false;
            }
        }

        if (canGenerate)
        {
            obstacles.emplace_back(Obstacle(SCREEN_WIDTH, GROUND_LEVEL, 50, 50, obstacleSpeed, renderer));
            nextObstacleTime = currentTime + (std::rand() % 3000 + 1000);
        }
        else
        {
            nextObstacleTime = currentTime + 500;
        }
    }

    for (auto &obstacle : obstacles)
    {
        obstacle.update();
    }

    for (auto &obstacle : obstacles)
    {
        obstacle.setSpeed(obstacleSpeed);
    }

    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                   [](const Obstacle &o)
                                   { return o.getRect().x + o.getRect().w < 0; }),
                    obstacles.end());
}

void ObstacleManager::render(SDL_Renderer *renderer)
{
    for (auto &obstacle : obstacles)
    {
        obstacle.render(renderer);
    }
}

const std::vector<Obstacle> &ObstacleManager::getObstacles() const
{
    return obstacles;
}
