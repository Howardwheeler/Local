#include "Game.hpp"

using std::cout;
using std::endl;

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){ //if true, successfully initialized SDL systems
        cout << "Subsystems Initialised!..." << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            cout << "Window created!..." << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Render created!..." << endl;
        }
        isRunning = true;
    } else{
        isRunning = false;
    }
}

void Game::handleEvents(){
    SDL_Event event; //makes a new event
    SDL_PollEvent(&event); //pulls the event to know where it is
    switch (event.type) //finds out what type of event it is
    {
    case SDL_QUIT: //if it quits, make isRunning false
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::update(){

}

void Game::render(){
    SDL_RenderClear(renderer); //clears first render and add new stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned!..." << endl;
}