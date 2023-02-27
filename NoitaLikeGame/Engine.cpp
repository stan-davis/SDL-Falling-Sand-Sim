#include "Engine.h"

int Engine::Init(int width, int height, const char* title)
{
    window_width = width;
    window_height = height;

    /*Initilize SDL*/
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if (window == NULL) return -1;

    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return -1;

    /*Initilize Graphics & Input*/
    graphics = new Graphics(renderer, width, height);
    if (graphics == nullptr) return -1;

    input = new Input();
    if (input == nullptr) return -1;

    return Start();
}

int Engine::Start()
{
    /*Called before game loop*/
    Ready();

    double current = SDL_GetTicks64();
    double previous = SDL_GetTicks64();
    double delta = 0;

    /*Game loop*/
    while (!quit)
    {
        /*Delta calculation*/
        previous = SDL_GetTicks64();
        delta = (previous - current) / 1000;
        current = previous;

        /*Updates*/
        ProcessEvents();
        input->PollState();
        Update(delta);
        input->UpdatePreviousInput();

        /*Rendering*/
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Render();
        graphics->Render();
        SDL_RenderPresent(renderer);

        /*FPS Cap*/
        SDL_Delay((1000 / 60) - delta);
    }

    delete input;
    delete graphics;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void Engine::ProcessEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quit = true;
    }
}