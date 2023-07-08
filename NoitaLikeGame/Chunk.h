#pragma once
#include <array>
#include <unordered_map>
#include "Pixel.h"
#include "EngineMath.h"
#include "Graphics.h"
#include "Tile.h"

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
	std::array<Pixel, area> pixels;
	std::vector<Tile> tiles;
	Vector2i position;

private:
	//Pixel sim
	void UpdateCell(int x, int y);
	void UpdateTile(const Tile& tile, const Pixel& p);
	bool IsEmpty(int x, int y);
	bool InBounds(int x, int y);
	void ClearUpdateBuffer();
	
	std::vector<Chunk*> neighbours;
	std::unordered_map<Vector2i, Chunk*> lookup;

	//box2d sim
	b2Vec2 gravity = b2Vec2(0.0f, 9.8f);
	b2World world = b2World(gravity);
};