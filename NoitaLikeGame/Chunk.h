#pragma once
#include <vector>
#include <unordered_map>
#include "Pixel.h"
#include "Math.h"
#include "Graphics.h"

class Chunk
{
public:
	Chunk(Vector2i offset);
	~Chunk() = default;

	void Update(double delta);
	void Draw(Graphics* graphics);

	void MovePixel(int x, int  y, int xto, int yto);
	void SetPixel(const Pixel& p, int x, int y);
	Pixel GetPixel(int x, int y);

	Vector2i GetPixelChunkCoords(int x, int y);

	void SetNeighbour(Chunk* neighbour);
	Chunk* GetNeighbour(int x, int y);

	static const int size = 256;
	static const int area = size * size;
	Vector2i position;
	std::vector<Pixel> pixels;

private:
	bool IsEmpty(int x, int y);
	bool InBounds(int x, int y);
	void ClearUpdateBuffer();
	
	std::vector<Chunk*> neighbours;
	std::unordered_map<Vector2i, Chunk*> lookup;
};