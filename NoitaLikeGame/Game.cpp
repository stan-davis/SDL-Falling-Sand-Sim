#include "Game.h"

int Game::init(int width, int height, const char* title)
{
    //SDL init
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if (window == NULL) return -1;

    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return -1;

    graphics = new Graphics(renderer, width, height);
    world = new World();

    //Run
    return run();
}

int Game::run()
{
    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 previous_time = 0;
    double delta_time = 0;
    
    //Game Loop
    while (!quit)
    {
        previous_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        delta_time = static_cast<double>(current_time - previous_time) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());

        processEvents();
        update(delta_time);
        render();
    }

    delete world;
    delete graphics;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void Game::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quit = true;
    }
}

void Game::update(double delta)
{
    world->Update(delta);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    world->Draw(graphics);
    graphics->Render();
    SDL_RenderPresent(renderer);
}
