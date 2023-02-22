#include "World.h"
#include <iostream>

World::World()
{
	for(int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			CreateChunk(x, y);
		}

	SetChunkNeighbours();
}

World::~World()
{
	for (auto* chunk : chunks)
		delete chunk;
}

void World::Update(double delta)
{
	for(auto& chunk : chunks)
		chunk->Update(delta);
}

void World::Draw(Graphics* graphics)
{
	for (auto& chunk : chunks)
		chunk->Draw(graphics);
}

Chunk* World::CreateChunk(int x, int y)
{
	if (x < 0 || x > size || y < 0 || y > size)
		return nullptr;

	Vector2i position = { x,y };
	Chunk* chunk = new Chunk(position);
	
	chunk_lookup.insert({ position, chunk});
	chunks.push_back(chunk);

	return chunk;
}

Chunk* World::GetChunk(int x, int y)
{
	if (x < 0 || x > size || y < 0 || y > size)
		return nullptr;

	Vector2i position = { x, y };

	auto itr = chunk_lookup.find(position);
	auto end = chunk_lookup.end();

	Chunk* chunk = itr != end ? itr->second : nullptr;

	return chunk;
}

void World::SetChunkNeighbours()
{
	for (auto& chunk : chunks)
	{
		Vector2i world_position = chunk->position;
		world_position.x = floor(static_cast<float>(world_position.x) / Chunk::size);
		world_position.y = floor(static_cast<float>(world_position.y) / Chunk::size);

		for(int x = world_position.x - 1; x <= world_position.x + 1; x++)
			for (int y = world_position.y - 1; y <= world_position.y + 1; y++)
			{
				if (x == world_position.x && y == world_position.y)
					continue;
				
				chunk->SetNeighbour(GetChunk(x, y));
			}
	}
}
