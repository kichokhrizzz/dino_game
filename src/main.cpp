
#include "Game.h"


int main(int argc, char *argv[])
{
    Game game;

    if(!game.init())
    {
        return 1;
    }

    while (game.running())
    {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(16);
    }

    return 0;     
}