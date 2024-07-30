#include "Game.h"
#include <iostream>

Game::Game()
    : window(nullptr), renderer(nullptr), font(nullptr), dino(nullptr), scoreManager(), obstacleManager(nullptr), groundTexture(nullptr), isRunning(true), gameOverTime(0), isGameOver(false) {}

Game::~Game()
{
    delete dino;
    delete obstacleManager;
    SDL_DestroyTexture(groundTexture);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/bit.ttf", 24);
    if (!font)
    {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    dino = new Dino(renderer);
    obstacleManager = new ObstacleManager(renderer);

    scoreManager.init(font);
    SDL_Surface *surface = IMG_Load("/Users/jhoselbadillocortes/Documents/chrome_dinosaur/assets/tileset.png");
    if (!surface)
    {
        std::cerr << "Failed to load ground image! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    groundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!groundTexture)
    {
        std::cerr << "Failed to create texture from ground image! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (!isGameOver)
        {
            dino->handleEvent(event);
        }
    }
}

void Game::update()
{
    if (isRunning)
    {
        if (!isGameOver)
        {
            dino->update();
            obstacleManager->update();
            scoreManager.update();

            if (checkCollision())
            {
                isGameOver = true;
                gameOverTime = SDL_GetTicks();
            }
        }
        else
        {
            if (SDL_GetTicks() - gameOverTime >= 5000)
            {
                isRunning = false;
            }
        }
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < SCREEN_WIDTH; x += TILE_WIDTH)
    {
        SDL_Rect srcRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect dstRect = {x, GROUND_LEVEL + 40, TILE_WIDTH, TILE_HEIGHT};
        SDL_RenderCopy(renderer, groundTexture, &srcRect, &dstRect);
    }

    dino->render(renderer);
    obstacleManager->render(renderer);
    scoreManager.render(renderer);

    if (isGameOver)
    {
        renderGameOver(renderer);
    }

    SDL_RenderPresent(renderer);
}

bool Game::checkCollision()
{
    for (const auto &obstacle : obstacleManager->getObstacles())
    {
        if (dino->checkCollision(obstacle.getRect()))
        {
            return true;
        }
    }
    return false;
}


void Game::renderGameOver(SDL_Renderer *renderer)
{
    SDL_Color textColor = {255, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Game Over", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth = 0;
    int textHeight = 0;
    TTF_SizeText(font, "Game Over", &textWidth, &textHeight);

    SDL_Rect renderQuad = {(SCREEN_WIDTH - textWidth) / 2, (SCREEN_HEIGHT - textHeight) / 2, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}