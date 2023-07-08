#pragma once
#include <SDL.h>
#include "Graphics.h"
#include "Input.h"

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	int Init(int width, int height, const char* title);

protected:
	virtual void Ready() = 0;
	virtual void Update(double delta) = 0;
	virtual void Render() = 0;

	int GetWindowWidth() { return window_width; }
	int GetWindowHeight() { return window_height; }
	Graphics* GetGraphics() { return graphics; }
	Input* GetInput() { return input; }

private:
	int Start();
	void ProcessEvents();

	//Init
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Graphics* graphics = NULL;
	Input* input = NULL;
	
	bool quit = false;
	int window_width = 0;
	int window_height = 0;
};

