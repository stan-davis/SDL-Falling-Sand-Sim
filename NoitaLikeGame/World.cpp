#include "World.h"
#include <iostream>

World::World()
{
	for(int x = 0; x < num_chunks; x++)
		for (int y = 0; y < num_chunks; y++)
		{
			CreateChunk(x * Chunk::size, y * Chunk::size);
		}
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
	if (x <= -size || x > size || y <= -size || y > size)
		return nullptr;

	Vector2i position = { x,y };
	Chunk* chunk = new Chunk(position);
	
	chunk_lookup.insert({ position, chunk });
	chunks.push_back(chunk);

	return chunk;
}

Chunk* World::GetChunk(int x, int y)
{
	Vector2i position = { SDL_floor(x / Chunk::size) * Chunk::size, SDL_floor(y / Chunk::size) * Chunk::size };

	auto itr = chunk_lookup.find(position);
	auto end = chunk_lookup.end();

	Chunk* chunk = itr != end ? itr->second : nullptr;

	return chunk ? chunk : CreateChunk(position.x, position.y);
}