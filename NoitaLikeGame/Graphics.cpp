#include "Graphics.h"

Graphics::Graphics(SDL_Renderer* _renderer, int _window_width, int _window_height) : renderer(_renderer), window_width(_window_width), window_height(_window_height)
{
	//Set up frame buffer
	frame_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
	pixels = new Uint32[window_width * window_height];
	memset(pixels, 0, window_width * window_height * sizeof(Uint32));
}

void Graphics::Render()
{
	SDL_UpdateTexture(frame_buffer, nullptr, pixels, window_width * sizeof(Uint32));
	memset(pixels, 0, window_width * window_height * sizeof(Uint32));
	SDL_RenderCopy(renderer, frame_buffer, NULL, NULL);
}

void Graphics::Draw(const SDL_Color& color, int x, int y)
{
	Vector2i world = Vector2i(x + camera_position.x, y + camera_position.y);

	if (world.x > 0 && world.x < window_width && world.y > 0 && world.y < window_height)
	{
		Uint32 c = ColorToUint(color);
		pixels[world.y * window_width + world.x] = c;
	}
}

void Graphics::SetCameraPosition(const Vector2i& position)
{
	camera_position = position;
}

Uint32 Graphics::ColorToUint(const SDL_Color& color)
{
	return (color.r << 0) + (color.g << 8) + (color.b << 16) + (color.a << 24);
}
