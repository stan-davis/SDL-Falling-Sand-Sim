#pragma once
#include <vector>
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

	const int& GetSize();
	const int& GetArea();
	const std::vector<Pixel>& GetPixels();

	Vector2i position;
private:
	void MovePixel(const Pixel& p, int x, int  y, int xto, int yto);
	void SetPixel(const Pixel& p, int x, int y);
	Pixel GetPixel(int x, int y);

	bool IsEmpty(int x, int y);
	bool InBounds(int x, int y);
	void ResetFrame();

	const int size = 256;
	std::vector<Pixel> pixels;
};