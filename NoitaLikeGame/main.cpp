#define SDL_MAIN_HANDLED
#include "Game.h"

int main()
{
	Game game;
	return game.Init(1024, 1024, "Falling Everything");
}