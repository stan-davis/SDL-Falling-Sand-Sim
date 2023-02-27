#pragma once
#include <SDL.h>
#include "EngineMath.h"

class Graphics
{
public:
	Graphics(SDL_Renderer* _renderer, int _window_width, int _window_height);
	~Graphics() = default;

	void Render();

	void Draw(const SDL_Color& color, int x, int y);
	void SetCameraPosition(const Vector2i& position);

private:
	Uint32 ColorToUint(const SDL_Color& color);

	//Init
	SDL_Renderer* renderer;
	int window_width;
	int window_height;

	//Frame Buffer
	SDL_Texture* frame_buffer;
	Uint32* pixels;

	//Camera
	Vector2i camera_position = Vector2i(0,0);
};

