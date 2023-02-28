#include "Chunk.h"
#include <iostream>

Chunk::Chunk(Vector2i offset) : position({ offset.x * size, offset.y * size })
{
	b2PolygonShape s_ship;
	s_ship.SetAsBox(1, 1);

	Tile ship = Tile({55,50}, b2_dynamicBody, s_ship, world);

	ship.data =
	{
					  {2,6},
			   {1,5}, {2,5},
		{0,4}, {1,4}, {2,4}, {3,4},
		{0,3}, {1,3}, {2,3}, {3,3},
		{0,2},               {3,2},
		{0,1},               {3,1},
		{0,0},               {3,0},
	};

	b2PolygonShape s_base;
	s_base.SetAsBox(9, 5);

	Tile base = Tile({ 47,100 }, b2_staticBody, s_base, world);

	base.data =
	{
		{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},
	};

	tiles.push_back(ship);
	tiles.push_back(base);
};

void Chunk::Update(double delta)
{
	ClearUpdateBuffer();

	/*Particle Sim*/
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			UpdateCell(x, y);
		}

	/*Physics Sim*/
	world.Step(delta, 6, 2);

	for (auto& tile : tiles)
		UpdateTile(tile, Rock());
}

void Chunk::Draw(Graphics* graphics)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			const Pixel& p = GetPixel(x, y);

			if (p.properties == Properties::EMPTY)
				continue;

			graphics->Draw(p.color, position.x + x, position.y + y);
		}

	for (auto& tile : tiles)
		UpdateTile(tile, Pixel());
}

void Chunk::UpdateCell(int x, int y)
{
	const Pixel& p = GetPixel(x, y);

	if (p.updated || p.properties == Properties::EMPTY || p.properties == Properties::STATIC)
		return;

	int dy = p.properties & Properties::MOVE_DOWN ? 1 : -1;
	int dx = (rand() % 2) * 2 - 1;

	for (int ry = p.vy; ry > 0; --ry)
		for (int rx = p.vx; rx > 0; --rx)
		{
			if (dy != 0 && IsEmpty(x, y + (dy * ry)))
			{
				MovePixel(x, y, x, y + (dy * ry));
				return;
			}
			else if (p.properties & Properties::MOVE_DIAGONAL && IsEmpty(x + (dx * rx), y + (dy * ry)))
			{
				MovePixel(x, y, x + (dx * rx), y + (dy * ry));
				return;
			}
			else if (p.properties & Properties::MOVE_DIAGONAL && IsEmpty(x + -(dx * rx), y + (dy * ry)))
			{
				MovePixel(x, y, x + -(dx * rx), y + (dy * ry));
				return;
			}
			else if (p.properties & Properties::MOVE_SIDE && IsEmpty(x + (dx * rx), y))
			{
				MovePixel(x, y, x + (dx * rx), y);
				return;
			}
			else if (p.properties & Properties::MOVE_SIDE && IsEmpty(x + -(dx * rx), y))
			{
				MovePixel(x, y, x + -(dx * rx), y);
				return;
			}
		}
}

void Chunk::UpdateTile(Tile& tile, const Pixel& p)
{
	for (auto pos : tile.data)
	{
		/*Rotate & Translate*/
		float a = tile.body->GetAngle();
		float c = cosf(a);
		float s = sinf(a);

		int rx = pos.x * c + pos.y * s;
		int ry = pos.y * c - pos.x * s;

		pos.x = rx + tile.body->GetPosition().x;
		pos.y = ry + tile.body->GetPosition().y;

		if (InBounds(pos.x, pos.y))
			SetPixel(p, pos.x, pos.y);
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

	Vector2i position = Vector2i(floor(static_cast<float>(neighbour->position.x) / size), floor(static_cast<float>(neighbour->position.y) / size));
	lookup.insert({ position, neighbour });
	neighbours.push_back(neighbour);
}

Chunk* Chunk::GetNeighbour(int x, int y)
{
	Vector2i position = Vector2i(floor(static_cast<float>(x) / size), floor(static_cast<float>(y) / size));

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
