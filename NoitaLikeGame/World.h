#pragma once
#include "Chunk.h"

class World
{
public:
	World();
	~World();

	void Update(double delta);
	void Draw(Graphics* graphics);

	void SetPixel(const Pixel& p, int x, int y);
	Chunk* GetChunk(int x, int y);
private:
	Chunk* CreateChunk(int x, int y);
	void SetChunkNeighbours();

	const int size = 2;

	std::vector<Chunk*> chunks;
	std::unordered_map<Vector2i, Chunk*> chunk_lookup;
};