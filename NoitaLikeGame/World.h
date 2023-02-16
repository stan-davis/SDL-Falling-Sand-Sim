#pragma once
#include <vector>
#include "Chunk.h"

class World
{
public:
	World();
	~World() = default;

	void Update(double delta);
	void Draw(Graphics* graphics);
private:
	//Chunks array
	const int num_chunks = 2;
	std::vector<Chunk> chunks;
};

