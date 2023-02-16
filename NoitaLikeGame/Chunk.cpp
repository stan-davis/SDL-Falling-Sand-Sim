#include "Chunk.h"

Chunk::Chunk(Vector2i offset) : position(offset)
{
	//Set up pixel array
	Pixel empty;

	for (int i = 0; i < area; i ++)
	{
		pixels.push_back(empty);
	}
}

void Chunk::Update(double delta)
{
	Sand sand;
	SetPixel(sand, 40, 200);

	ResetFrame();

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			const Pixel& p = GetPixel(x, y);

			if (p.updated || p.properties & Pixel::Properties::EMPTY || p.properties & Pixel::Properties::STATIC)
				continue;

			int dy = p.properties & Pixel::Properties::MOVE_DOWN ? 1 : -1;
			int dx = (rand() % 2) * 2 - 1;

			if (p.properties & Pixel::Properties::MOVE_DOWN && IsEmpty(x, y + 1))
			{
				MovePixel(x, y, x, y + 1);
			}
			else if (p.properties & Pixel::Properties::MOVE_UP && IsEmpty(x, y - 1))
			{
				MovePixel(x, y, x, y - 1);
			}
			else if (p.properties & Pixel::Properties::MOVE_DIAGONAL && IsEmpty(x + dx, y + dy))
			{
				MovePixel(x, y, x + dx, y + dy);
			}
			else if (p.properties & Pixel::Properties::MOVE_SIDE && IsEmpty(x + dx, y))
			{
				MovePixel(x, y, x + dx, y);
			}
		}
}

void Chunk::Draw(Graphics* graphics)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			const Pixel::Color& c = GetPixel(x, y).color;
			SDL_Color color = { c.r, c.g, c.b };
			graphics->Draw(color, position.x + x, position.y + y);
		}
}

const std::vector<Pixel>& Chunk::GetPixels()
{
	return pixels;
}

void Chunk::MovePixel(int x, int y, int xto, int yto)
{
	if (InBounds(xto, yto))
	{
		const Pixel& pixel = GetPixel(x, y);
		const Pixel& origin = GetPixel(xto, yto);

		SetPixel(pixel, xto, yto);
		SetPixel(origin, x, y);
	}
	else
	{
		//Find in neighbouring chunk
	}
}

void Chunk::SetPixel(const Pixel& p, int x, int y)
{
	pixels[y * size + x] = p;
	pixels[y * size + x].updated = true;
}

Pixel Chunk::GetPixel(int x, int y)
{
	return pixels[y * size + x];
}

bool Chunk::IsEmpty(int x, int y)
{
	if (InBounds(x, y))
	{
		return GetPixel(x, y).properties == Pixel::Properties::EMPTY;
	}
	else
	{
		//Find in neighbouring chunk
		return false;
	}
}

bool Chunk::InBounds(int x, int y)
{
	return x >= 0 && y >= 0 && x < size && y < size;
}

void Chunk::ResetFrame()
{
	for (auto& pixel : pixels)
	{
		pixel.updated = false;
	}
}
