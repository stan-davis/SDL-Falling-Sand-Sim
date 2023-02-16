#include "World.h"

World::World()
{
	for(int x = 0; x < num_chunks; x++)
		for (int y = 0; y < num_chunks; y++)
		{
			const int chunk_size = 256;
			Chunk chunk = Chunk({ chunk_size * x, chunk_size * y });
			chunks.push_back(chunk);
		}
}

void World::Update(double delta)
{
	for(auto& chunk : chunks)
		chunk.Update(delta);
}

void World::Draw(Graphics* graphics)
{
	for (auto& chunk : chunks)
		chunk.Draw(graphics);
}
