#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ScoreManager
{
public:
    ScoreManager();
    void init(TTF_Font *font);
    void update();
    void render(SDL_Renderer *renderer);

private:
    int score;
    Uint32 startTime;
    Uint32 lastUpdateTime;
    TTF_Font *font;
};

#endif