#pragma once

struct Pixel
{
	enum Properties
	{
		EMPTY			= 0b00000000,
		STATIC			= 0b00000010,
		MOVE_DOWN		= 0b00000100,
		MOVE_UP			= 0b00001000,
		MOVE_DIAGONAL	= 0b00010000,
		MOVE_SIDE		= 0b00100000,
	};

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	unsigned char properties = Properties::EMPTY;
	Color color = {0,0,0};
	bool updated = false;

	//properties (how it interacts with the world) 1 byte
	//color (color of the pixel) 4 bytes
	//has_been_updated (whether the current pixel has been updated in game) 1 byte
	//total: 6 bytes (48 bits)
};

//Elements definitions
struct Sand : public Pixel
{
	Sand()
	{
		color = { 255, 255, 0 };
		properties = Properties::MOVE_DOWN | Properties::MOVE_DIAGONAL;
	}
};