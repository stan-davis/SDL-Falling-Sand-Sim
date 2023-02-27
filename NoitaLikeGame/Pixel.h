#pragma once
#include "SDL.h"

enum class Properties : Uint8
{
	EMPTY			= 0b00000000,
	STATIC			= 0b00000010,
	MOVE_DOWN		= 0b00000100,
	MOVE_UP			= 0b00001000,
	MOVE_DIAGONAL	= 0b00010000,
	MOVE_SIDE		= 0b00100000,
};

inline auto operator|(Properties a, Properties b)
{
	return Properties(static_cast<Uint8>(a) | static_cast<Uint8>(b));
}

inline auto operator&(Properties a, Properties b)
{
	return static_cast<Uint8>(a) & static_cast<Uint8>(b);
}

struct Pixel
{
	SDL_Color color = { 0,0,0 };
	Properties properties = Properties::EMPTY;
	Uint8 vx = 1, vy = 1;
	bool updated = false;
};

//Element def
struct Sand : public Pixel
{
	Sand()
	{
		color = { 255, 255, 0 };
		properties = Properties::MOVE_DOWN | Properties::MOVE_DIAGONAL;
		vy = 3;
	}
};

struct Water : public Pixel
{
	Water()
	{
		color = { 0,0,255 };
		properties = Properties::MOVE_DOWN | Properties::MOVE_SIDE | Properties::MOVE_DIAGONAL;
		vx = 4;
		vy = 3;
	}
};

struct Rock : public Pixel
{
	Rock()
	{
		color = { 155,155,155 };
		properties = Properties::STATIC;
	}
};