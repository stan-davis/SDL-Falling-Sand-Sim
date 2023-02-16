#include "Graphics.h"

Graphics::Graphics(SDL_Renderer* _renderer, int _window_width, int _window_height) : renderer(_renderer), window_width(_window_width), window_height(_window_height)
{
	//Set up frame buffer
	frame_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
	frame_buffer_size = (window_width * window_height) * 3 * sizeof(Uint8);
	dst = { 0, 0, window_width, window_height };

	//Set up color buffer
	for (int i = 0; i < window_width * window_height; i++)
		pixels.push_back(SDL_Color());
}

void Graphics::Render()
{
	auto* frame = static_cast<Uint8*>(malloc(frame_buffer_size));
	memset(frame, 0, frame_buffer_size);

	for (int x = 0; x < window_width; x++)
		for (int y = 0; y < window_height; y++)
		{
			int index = y * window_width + x;
			const unsigned int offset = (window_width * 3 * y) + x * 3;

			frame[offset + 0] = pixels[index].r;
			frame[offset + 1] = pixels[index].g;
			frame[offset + 2] = pixels[index].b;
		}

	SDL_UpdateTexture(frame_buffer, nullptr, frame, window_width * 3);
	free(frame);
	SDL_RenderCopy(renderer, frame_buffer, nullptr, &dst);
}

void Graphics::Draw(const SDL_Color& color, int x, int y)
{
	if (x > 0 && x <= window_width && y > 0 && y <= window_height)
		pixels[y * window_width + x] = color;
}
