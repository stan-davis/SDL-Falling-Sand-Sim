#pragma once
#include "EngineMath.h"
#include "box2d.h"
#include <vector>

class Tile
{
public:
	Tile(Vector2 position, b2BodyType type, b2Shape& shape, b2World& world);
	~Tile() = default;

	std::vector<Vector2i> data;
	b2Body* body = nullptr;
};

