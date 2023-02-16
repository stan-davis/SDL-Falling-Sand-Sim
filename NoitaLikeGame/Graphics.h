#pragma once
#include <SDL.h>
#include <vector>

class Graphics
{
public:
	Graphics(SDL_Renderer* _renderer, int _window_width, int _window_height);
	~Graphics() = default;

	void Render();
	void Draw(const SDL_Color& color, int x, int y);

private:
	SDL_Renderer* renderer;
	int window_width;
	int window_height;

	SDL_Texture* frame_buffer;
	size_t frame_buffer_size;
	SDL_Rect dst;
	std::vector<SDL_Color> pixels;
};

