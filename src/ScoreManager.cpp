#include "ScoreManager.h"
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Constants.h"

ScoreManager::ScoreManager() : score(0), startTime(0), lastUpdateTime(0), font(nullptr) {}

void ScoreManager::init(TTF_Font *font)
{
    this->font = font;
    startTime = SDL_GetTicks();
    lastUpdateTime = startTime;
}

void ScoreManager::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime >= 1000)
    {
        score++;
        lastUpdateTime = currentTime;
    }
}

void ScoreManager::render(SDL_Renderer *renderer)
{
    SDL_Color textColor = {0, 0, 0, 255};
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect renderQuad = {SCREEN_WIDTH - textWidth - 10, 10, textWidth, textHeight};
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    SDL_DestroyTexture(textTexture);
}