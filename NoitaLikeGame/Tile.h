#pragma once
#include "EngineMath.h"
#include "box2d.h"
#include <vector>

class Tile
{
public:
	Tile(Vector2 position, b2BodyType type, b2World& world);
	~Tile() = default;

	void Update();

	std::vector<Vector2i> data;
	Transform transform;
	b2Body* body = nullptr;
};

