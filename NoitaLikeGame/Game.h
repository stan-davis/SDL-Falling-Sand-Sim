#pragma once
#include <SDL.h>
#include <memory>
#include "World.h"
#include "Graphics.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	int init(int width, int height, const char* title);
private:
	//Engine
	int run();
	void processEvents();
	void update(double delta);
	void render();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	bool quit = false;

	//World
	Graphics* graphics;
	World* world;
};

