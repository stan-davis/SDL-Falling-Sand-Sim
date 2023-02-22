#include "Chunk.h"
#include <iostream>

Chunk::Chunk(Vector2i offset) : position({ offset.x * size, offset.y * size})
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

	ClearUpdateBuffer();

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			const Pixel& p = GetPixel(x, y);

			if (p.updated || p.properties == Properties::EMPTY || p.properties == Properties::STATIC)
				continue;

			int dy = p.properties & Properties::MOVE_DOWN ? 1 : -1;
			int dx = (rand() % 2) * 2 - 1;

			if (dy != 0 && IsEmpty(x, y + dy))
			{
				MovePixel(x, y, x, y + dy);
			}
			else if (p.properties & Properties::MOVE_DIAGONAL)
			{
				if (IsEmpty(x + dx, y + dy))
					MovePixel(x, y, x + dx, y + dy);
				else
				{
					dx *= -1;

					if (IsEmpty(x + dx, y + dy))
						MovePixel(x, y, x + dx, y + dy);
				}
			}
			else if (p.properties & Properties::MOVE_SIDE)
			{
				if (IsEmpty(x + dx, y))
					MovePixel(x, y, x + dx, y);
				else
				{
					dx *= -1;

					if (IsEmpty(x + dx, y))
						MovePixel(x, y, x + dx, y);
				}
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

void Chunk::MovePixel(int x, int y, int xto, int yto)
{
	if (InBounds(xto, yto))
	{
		const Pixel& current = GetPixel(x, y);
		const Pixel& destination = GetPixel(xto, yto);

		SetPixel(current, xto, yto);
		SetPixel(destination, x, y);
	}
	else
	{
		Vector2i world_to = { xto + position.x , yto + position.y };

		if (Chunk* dst = GetNeighbour(world_to.x, world_to.y))
		{
			Vector2i to = dst->GetPixelChunkCoords(world_to.x, world_to.y);

			const Pixel& current = GetPixel(x, y);
			const Pixel& destination = dst->GetPixel(to.x, to.y);

			dst->SetPixel(current, to.x, to.y);
			SetPixel(destination, x, y);
		}
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

Vector2i Chunk::GetPixelChunkCoords(int x, int y)
{
	return { x - position.x , y - position.y };
}

void Chunk::SetNeighbour(Chunk* neighbour)
{
	if (neighbour == nullptr)
		return;

	Vector2i position = { floor(static_cast<float>(neighbour->position.x) / size), floor(static_cast<float>(neighbour->position.y) / size) };
	lookup.insert({ position, neighbour });
	neighbours.push_back(neighbour);
}

Chunk* Chunk::GetNeighbour(int x, int y)
{
	Vector2i position = { floor(static_cast<float>(x) / size), floor(static_cast<float>(y) / size) };

	auto itr = lookup.find(position);
	auto end = lookup.end();

	Chunk* chunk = itr != end ? itr->second : nullptr;

	return chunk;
}

bool Chunk::IsEmpty(int x, int y)
{
	if (InBounds(x, y))
	{
		return GetPixel(x, y).properties == Properties::EMPTY;
	}

	Vector2i world_position = { x + position.x , y + position.y };

	if (Chunk* dst = GetNeighbour(world_position.x, world_position.y))
	{
		Vector2i to = dst->GetPixelChunkCoords(world_position.x, world_position.y);
		return dst->GetPixel(to.x, to.y).properties == Properties::EMPTY;
	}

	return false;
}

bool Chunk::InBounds(int x, int y)
{
	return x >= 0 && x < size && y >= 0 && y < size;
}

void Chunk::ClearUpdateBuffer()
{
	for (auto& pixel : pixels)
	{
		pixel.updated = false;
	}
}
