#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Dino.h"
#include "Obstacle.h"
#include "ScoreManager.h"
#include "ObstacleManager.h"
#include "Constants.h"

class Game
{
public:
    Game();
    ~Game();
    bool init();
    void handleEvents();
    void update();
    void render();
    bool running() { return isRunning; }
    bool checkCollision();
    void renderGameOver(SDL_Renderer *renderer);
    Uint32 gameOverTime;
    bool isGameOver;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    Dino *dino;
    ScoreManager scoreManager;
    ObstacleManager *obstacleManager;
    bool isRunning;
    SDL_Texture *groundTexture;
};

#endif