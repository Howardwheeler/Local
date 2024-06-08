#include "Game.hpp"
#include <iostream>

Game *game = nullptr;

int SDL_main(int argc, const char *argv[]){

    game = new Game();

    game->init("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, false);

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
};