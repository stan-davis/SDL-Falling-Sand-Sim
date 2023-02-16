#pragma once
#include "SDL.h"

struct Vector2
{
	float x = 0;
	float y = 0;

	float Length()
	{
		return SDL_sqrtf((x * x) + (y * y));
	}

	Vector2 Normalized()
	{
		return Vector2{ x / Length(), y / Length() };
	}
};

struct Vector2i
{
	int x = 0;
	int y = 0;

	float Length()
	{
		return SDL_sqrtf((x * x) + (y * y));
	}
};