#define SDL_MAIN_HANDLED
#include "Game.h"
#include <iostream>

int main()
{
    Game game;
    return game.init(1024, 1024, "Falling Everything");
}